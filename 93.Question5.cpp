#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <functional>
#include <future>
#include <variant>
#include <ranges>

class Ingredient{                                                           // abstraction for all ingredients
    public:
        virtual auto name() -> std::string = 0;     
        virtual auto calories() -> int = 0;
        virtual auto cost() -> int = 0;
};

class Bread : public Ingredient{                                            // abstraction for bread
    public:
        virtual auto name() -> std::string = 0;
        virtual auto calories() -> int = 0;
        virtual auto cost() -> int = 0;
};

template<typename S, typename I>                                            //*M
class Bagel : public Bread{
    public:
        auto name() noexcept -> std::string override {                      //*M (using noexcept)
            return "Bagel";
        }
        auto calories() noexcept -> int override{
            return 599;
        }
        auto cost() noexcept -> int override{
            return 230;
        }
};

class Filling : public Ingredient{
    public:
        virtual auto name() -> std::string = 0;
        virtual auto calories() -> int = 0;
        virtual auto cost() -> int = 0;
};

template<typename S, typename I>
class Cheese: public Filling{
    public:
        auto name() noexcept -> std::string override {                      //*M (using noexcept)
            return "Cheese";
        }
        auto calories() noexcept -> int override{
            return 239;
        }
        auto cost() noexcept -> int override{
            return 120;
        }
};

template<typename S, typename I>
class Meat: public Filling{
    public:
        auto name() noexcept -> std::string override {                      //*M (using noexcept)
            return "Meat";
        }
        auto calories() noexcept -> int override{
            return 140;
        }
        auto cost() noexcept -> int override{
            return 145;
        }
};


// creating a class to represent sandwich builder
class Sandwich{
    private:
        std::vector<std::shared_ptr<Ingredient>> ingredients;

    public:
        void addIngredients(std::shared_ptr<Ingredient> ingredient){
            ingredients.emplace_back(ingredient);
        }
        void printSandwich(){
            for(std::shared_ptr<Ingredient> x: ingredients){
                std::cout<< x->name() << " : "<< x->calories() <<" : "<< x->cost() << std::endl;
            }
        }
        
        void getTotalCalories(){
            int totalCalories = 0;
            for(std::shared_ptr<Ingredient> x: ingredients){
                totalCalories += x->calories();
            }
            std::cout<<"Total Calories: "<<totalCalories<<std::endl;
        }

        auto calculateCost() noexcept -> int{
            int totalCost = 0;
            for(const auto& it : ingredients){
                totalCost += it->cost();
            }
            return totalCost;
        }
};

class SandwichBuilder{
    public:
    static std::shared_ptr<Sandwich> readyMade(){
        std::shared_ptr<Sandwich> sandwich = std::make_shared<Sandwich>();
        sandwich -> addIngredients(std::make_shared<Bagel<std::string, int>>());
        sandwich -> addIngredients(std::make_shared<Cheese<std::string, int>>());
        sandwich -> addIngredients(std::make_shared<Meat<std::string, int>>());

        return sandwich;
    }

    static auto build(std::shared_ptr<Sandwich> s, std::shared_ptr<Ingredient> ingredient) -> std::shared_ptr<Sandwich>{
        s -> addIngredients(ingredient);
        return s;
    }
};


// Sandwich Visitor
class GenerateBill{
    public:
        void operator()(std::shared_ptr<Sandwich> sandwich) {
            std::cout << "Total Cost : "<< sandwich->calculateCost() << std::endl;
        }
};


int main(){
    std::cout<<"Sandwich Builder"<<std::endl;
    std::shared_ptr<Sandwich> custom = std::make_shared<Sandwich>();

    SandwichBuilder::build(custom, std::make_shared<Bagel<std::string, int>>());
    SandwichBuilder::build(custom, std::make_shared<Cheese<std::string, int>>());

    std::cout<<"Ready Made:\n";
    std::shared_ptr<Sandwich> myself = SandwichBuilder::readyMade();


    using SandwichType = std::variant<std::shared_ptr<Sandwich>>;               // variant for sandwich
    std::vector<SandwichType> mySandwiches {custom, myself};                    // vector of variants


    GenerateBill generateBill;                                                 
    auto visitable = [&](const auto& visitor){
        std::visit(generateBill, visitor);                                      // sandwich will visit generateBill for generating bill
    };
    for(const auto& sandwichSequence: mySandwiches){
        visitable( sandwichSequence );
    }   
}
