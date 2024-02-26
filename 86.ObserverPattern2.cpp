#include <iostream>
#include <functional>
#include <vector>
#include <string>
 
struct Observed
{
    using observer = std::function< void( const Observed& ) > ;
 
    template < typename FN, typename... EXTRA_ARGS >
    void registerObserver( FN&& fn, EXTRA_ARGS&&... extra_args )
    {
        using std::placeholders::_1 ;
        // this is where bind is bringing fn and Arg together
        
        observers.emplace_back( std::bind( std::forward<FN>(fn), _1, std::forward<EXTRA_ARGS>(extra_args)... ) ) ;
    }
 
    int value() const { return val ; }
    void value( int v ) { if( val != v ) { val = v ; report_value_changed() ; } }
 
    private:
        std::vector<observer> observers ;
        int val = 0 ;
 
    void report_value_changed() { for( auto& fn : observers ) fn(*this) ;
        
    }
};
 
int foo( const Observed& sender, int a, int b )
{
    std::cout << "foo - sender: " << std::addressof(sender) << " a: " << a << " b: " << b << '\n' ;
    return sender.value() + a + b ;
}
 
int main()
{
    Observed obj ;
    const auto handler = []( const Observed& sender, std::string info )
    { std::cout << "closure - sender: " << std::addressof(sender) << " info: " << info << '\n' ; } ;
 
    obj.registerObserver( handler, std::string("hello") ) ;
    obj.registerObserver( foo, 23, 9456 ) ;
 
    struct CallbackObserver
    {
        void handle_value_changed( const Observed& sender ) const
        { std::cout << "CallbackObserver::handle_value_changed - sender: " << std::addressof(sender) << '\n' ; }
        // ...
    };
 
    CallbackObserver this_observer ;
    obj.registerObserver( std::bind( &CallbackObserver::handle_value_changed, std::ref(this_observer),
                                      std::placeholders::_1 ) ) ;
 
    obj.value(10) ;
}
/*
closure - sender: 0x16fdff160 info: hello
foo - sender: 0x16fdff160 a: 23 b: 9456
CallbackObserver::handle_value_changed - sender: 0x16fdff160
Program ended with exit code: 0
*/