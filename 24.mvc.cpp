/*
MVC : Model View Controller
*/

#include <iostream>

class CounterModel{
    private:
        int count;
    public:
        CounterModel() : count(0){}
        
        constexpr int getCount() const{
            return count;
        }

        void inc(){
            count++;
        }
};

class CounterView{
    public:
        void displayCount(int count){
            std::cout<<"Count: "<<count<<std::endl;
        }
};

class CounterController{
    private:
        CounterModel& model;
        CounterView& view;

    public:
        CounterController(CounterModel& m, CounterView& v) : model(m), view(v){}

        void increment(){
            model.inc();
            auto x = [&](){
                view.displayCount(model.getCount());
            };
            x();
        }
        void updateView() const{
            view.displayCount(model.getCount());
        }
};

int main(){
    std::cout<<"MVC Framework!"<<std::endl;

    CounterModel model;
    CounterView view;
    CounterController controller(model, view);

    controller.updateView();
    controller.increment();
    controller.increment();
    // controller.updateView();

}