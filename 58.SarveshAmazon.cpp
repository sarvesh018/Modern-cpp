#include <iostream>
#include <functional>
#include <variant>
#include <vector>
#include <memory>

// Product type
enum class Type {TOY, GADGET, CLOTHES};

// to check price of products is in integer datatype
template <typename T>         // *M
concept MandateData = requires(T t){
    requires std::is_same_v<decltype(t), int>;
};

// Category interface
class Category{
    public:
        using product = std::function<void()>;
        virtual void getProductDetials () = 0;
        virtual Type getType() = 0;
        virtual int64_t getCost() = 0;
        virtual product registerProduct() = 0;
};

// TOY Category
class Toy : public Category{
    public:    

        // taking details as rValue
        template<MandateData T>                             // *M ----> forwarding rValue using move construct
        Toy(std::string&& s, std::string&& _id, T&& c) : name(std::move(s)), id(std::move(_id)), cost(std::move(c)){
            type = Type::TOY;
        }        

        // using lambda to register product
        product registerProduct() override {  // *M ---> overriding methonds
            return [&](){
                std::cout<<"ID: "<<id<<", Name: "<<name<<", Cost: "<<cost<<std::endl;
            };
        }

        // get cost of the product
        int64_t getCost() noexcept override {
            return cost;
        }

        // get product type
        Type getType() override{
            return type;
        }

        // get product info
        void getProductDetials() override{
            std::cout<<"ID: "<<id<<", Name: "<<name<<", Cost: "<<cost<<std::endl;
        }
    private:
        std::string name, id;
        int64_t cost;
        Type type;
};


// GADGET Category

class Gadget : public Category{
    public:
        template<MandateData T>
        Gadget(std::string&& s, std::string&& _id, T&& c) : name(std::move(s)), id(std::move(_id)), cost(std::move(c)){ // *M
            type = Type::GADGET;
        }        
    
        product registerProduct() override {     // *M ---> overriding methonds
            return [&](){
                std::cout<<"ID: "<<id<<", Name: "<<name<<", Cost: "<<cost<<std::endl;
            };
        }
    
        int64_t getCost() noexcept override{        // *M (noexpect)
            return cost;
        }
    
        Type getType() override{
            return type;
        }
    
        void getProductDetials() override{
            std::cout<<"ID: "<<id<<", Name: "<<name<<", Cost: "<<cost<<std::endl;
        }
    
    private:
        std::string name, id;
        int64_t cost;
        Type type;
};


// CLOTHES Category
class Clothes : public Category{
    public:        
        template<MandateData T>
        Clothes(std::string&& s, std::string&& _id, T&& c) : name(std::move(s)), id(std::move(_id)), cost(std::move(c)){ // *M
            type = Type::CLOTHES;
        }        
        
        product registerProduct() override {     // *M ---> overriding methonds
            return [&](){
                std::cout<<"ID: "<<id<<", Name: "<<name<<", Cost: "<<cost<<std::endl;
            };
        }
        
        int64_t getCost() noexcept override{    // *M
            return cost;
        }
        
        Type getType() override{
            return type;
        }
        
        void getProductDetials() override{
            std::cout<<"ID: "<<id<<", Name: "<<name<<", Cost: "<<cost<<std::endl;
        }
    private:
        std::string name, id;
        int64_t cost;
        Type type;
};



// CART class to store to the details of all the purchased products
class Cart{
    private:
        std::vector<Category*> myCart;             // myCart will contain items selected by user
    public:
        void addProductToMyCart(Category* product){
            myCart.emplace_back(product);       // adding product into cart
        }   
       
        int64_t generateBill(){                 // calculate total amount of all the items
            int64_t total = 0;
            for(const auto& i : myCart){        //*M
                total += i->getCost();
            }
            return total;
        }
       
        void cartDetails(){                    // print cart details
            for(const auto& i: myCart){
                i->getProductDetials();
            }
        }

        int64_t getSize(){
            return myCart.size();
        }
};

class User{
    public:
        Cart cart;
        std::string name;
        std::string address;
        bool flag;

        User(){
            flag = false;                           // initially user not registered
        }
    
        void addProduct(Category* product){
            cart.addProductToMyCart(product);       // add selected items by user into cart
        }   

        void registerUser(std::string _name, std::string _address){
            flag = true;
            name = _name;                           // register user detials
            address = _address;
        }

        void totalBill(){
            std::cout<<"\nTotal Bill: "<<cart.generateBill()<<std::endl;
        }
       
        void viewCart(){
            std::cout<<std::endl;                   // view user's cart
            cart.cartDetails();
        }

        bool hasItemsInCart(){
            return (cart.getSize() > 0) ? true : false;
        }
};


class Manager{                                      // manager will have details of users and items with it types
    private:
        // map of [type, lambda]
        std::unordered_map<Type, std::vector<std::function<void()>>> products;
        std::vector<User> users;
    public:
        
        Manager(){
            std::vector<std::function<void()>> vec;
            products[Type::TOY] = vec;
            products[Type::CLOTHES] = vec;
            products[Type::GADGET] = vec;
        }
        
        void addNewProduct(Category* product){         // add product by identifing its type
            products[product->getType()].emplace_back(product->registerProduct());
        }

        void showAllProducts(){
            std::cout<<"TOYS Category: "<<std::endl;
            for(const auto& prod: products[Type::TOY]){        //*M
                prod();
            }
            std::cout<<"CLOTHES Category: "<<std::endl;
            for(const auto& prod: products[Type::CLOTHES]){    //*M
                prod(); 
            }
            std::cout<<"GADGETS Category: "<<std::endl;
            for(const auto& prod: products[Type::GADGET]){     //*M
                prod();
            }
        }
        
        void registerUser(User& user){
            users.emplace_back(user);
        }

        // deliver items to all the users if they registered
        void deliveryItems(){
            for(const auto& user : users){
                if(user.flag){
                    std::cout<<"Item Delivered to "<<user.name<<" on this address -> "<<user.address<<std::endl;
                }
                else{
                    std::cout<<"User not registered!!"<<std::endl;
                }
            }
        }        
};

int main(){
    Manager manager;
    Category* car = new Toy("Racing Car", "T1500", 4200);
    Category* gun = new Toy("Gun", "T2450", 5400);
    Category* shirt = new Clothes ("Shirt", "SH123", 949);
    Category* jeans = new Clothes ("Jeans", "JN45A", 529);
    Category* watch = new Gadget ("Watch", "SH123", 57999);
    Category* tv = new Gadget ("TV", "SH123", 63799);

    // toy1->getProductDetials();

    manager.addNewProduct(car);
    manager.addNewProduct(gun);
    manager.addNewProduct(shirt);
    manager.addNewProduct(jeans);
    manager.addNewProduct(watch);
    manager.addNewProduct(tv);

    manager.showAllProducts();

    User user1;
    user1.registerUser("Sarvesh", "123 Street");
    user1.addProduct(car);
    user1.addProduct(gun);
    user1.addProduct(watch);
    user1.viewCart();
    user1.totalBill();

    // if cartSize > 0 than only we register the user
    if(user1.hasItemsInCart()){
        manager.registerUser(user1);
    }

    User user2;
    user2.addProduct(shirt);
    user2.addProduct(tv);
    user2.addProduct(jeans);
    user2.viewCart();
    user2.totalBill();

    if(user1.hasItemsInCart()){
        manager.registerUser(user2);
    }
    
    // Deliver products
    manager.deliveryItems();
}
