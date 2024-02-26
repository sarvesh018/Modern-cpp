#include <iostream>
#include <thread>
#include <mutex>
#include <functional>
#include <future>
#include <condition_variable>
#include <queue>
#include <vector>

class ThreadPool{
    private:
        std::vector< std::thread >              workerThreads;
        std::queue< std::function< void() >>    queuedTasks;
        std::mutex                              queueMutex;
        std::condition_variable                 condition;
        bool                                    stop;

    public:
        ThreadPool( size_t numThreads ) : stop(false) {
            for(size_t i=0; i < numThreads; i++){
                std::cout<<"\n------"<<i+1<<" Thread created"<<std::endl;
                workerThreads.emplace_back(
                    [ this ](){
                        while(true){
                            std::function< void() > pullAsyncTaskFromQueueToExecute;
                            {
                                // unnamed space
                                // gets fired when we notify from the queue
                                std::unique_lock< std::mutex > lock(queueMutex);
                                condition.wait(lock,
                                    [this]{
                                        return stop || !queuedTasks.empty();
                                    }
                                );
                                
                                if(stop && queuedTasks.empty()) return;

                                pullAsyncTaskFromQueueToExecute = std::move( queuedTasks.front());
                                queuedTasks.pop();
                            }
                            std::cout<<"\nState : Lambda is ready for the execution"<<std::endl;
                            pullAsyncTaskFromQueueToExecute();
                        }   
                    }       
                );
            }
        } // ThreadPool Constructor

        // enqueue
        template<typename F, typename... Args>
        auto enqueue(F&& f, Args&&... args) -> std::future< typename std::invoke_result<F, Args...>::type>
        {
            using returnType = typename std::invoke_result< F, Args... >::type;
            std::cout<<"\nState : Lambda invoked "<<std::endl;

            auto prepareAsyncTask = std::make_shared< std::packaged_task<returnType()>>(
                std::bind(std::forward<F>(f), std::forward<Args...>(args)...));

            // lets get the handle of our async task...
            std::future< returnType > result = prepareAsyncTask->get_future();

            {
                std::cout<<"\nState : Lambda is prepared for execution" << std::endl;
                std::unique_lock< std::mutex > lock (queueMutex);

                if(stop) throw std::runtime_error("Enqueue on stoped thread pool");

                // [](){}() -> function calling itself (unnamed function)

                queuedTasks.emplace([prepareAsyncTask](){(*prepareAsyncTask)();});
                condition.notify_one();

                return result;
            }

        }   // end of enqueue

        ~ThreadPool(){
            {
                std::unique_lock<std::mutex> lock(queueMutex);
                stop = true;
            }
            condition.notify_all();
            for(std::thread& i : workerThreads){
                i.join();
            }
        }
};

int main(){
    ThreadPool pool(4);

    auto task1 = pool.enqueue( [](){ std::cout<<"Task 1 executed..."<<std::endl; });
    auto task2 = pool.enqueue( [](){ std::cout<<"Task 2 executed..."<<std::endl; });

    // auto task3 = pool.enqueue( [](int a, int b){ std::cout<<"Task 3 executed... "<<a+b<<std::endl; }, 10, 20);
    if(int x=5 ; x==15){
    std::cout<<"x: "<<x<<std::endl;
    }
    else{
       std::cout<<"x is not 15: "<<x<<std::endl;
    }

}  