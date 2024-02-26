#include <iostream>
#include <mutex>
#include <memory>
#include <functional>

template<typename T>
class Lazy{
    public:
        template <typename F, typename... Args>
        Lazy(F&& f, Args&&... args) :
            m_func(std::bind(std::forward<F>(f), std::forward<Args>(args)...)) {}
        

        const auto& get(){
            std::cout<<"At get returns single data"<<std::endl;

            std::call_once(m_flag, [this](){m_data = std::make_unique<T>( m_func()); });

            return *m_data;
        }

    private:
        std::unique_ptr<T> m_data;
        std::function<T()> m_func;
        std::once_flag     m_flag;
};

int main(){
    std::string str("Hello World");

    auto lazy_str = Lazy<std::string>( [str](){ return str; });

    std::cout<< lazy_str.get() << std::endl;
}
