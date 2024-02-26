#include <bits/stdc++.h>
class Ingredient{
    public:
        virtual std::string name() = 0;
        virtual int calories() = 0;
        virtual int cost() = 0;
};

class Bread : public Ingredient{
    public:
        virtual std::string name() = 0;
        virtual int calories() = 0;
        virtual int cost() = 0;
};

class Bage1 : public Bread{
    public:
        std::string name() override{
            return "Bage1";
        }
        int calories() override{
            return 150;
        }
        int cost() override{
            return 100;
        }
};

class Bage2 : public Bread{
    public:
        std::string name() override{
            return "Bage2";
        }
        int calories() override{
            return 170;
        }
        int cost() override{
            return 80;
        }
};

class Filling : public Ingredient{
    public:
        virtual std::string name() = 0;
        virtual int calories() = 0;
        virtual int cost() = 0;
};

class Cheese: public Filling{
    public:
        std::string name() override{
            return "Cheese";
        }
        int calories() override{
            return 150;
        }
        int cost() override{
            return 30;
        }
};

class Meat: public Filling{
    public:
        std::string name() override{
            return "Meat";
        }
        int calories() override{
            return 200;
        }
        int cost() override{
            return 60;
        }
};


// creating a class to represent sandwich builder
class Sandwich{
    private:
        std::vector<Ingredient*> ingredients;

    public:
        void addIngredients(Ingredient* ingredient){
            ingredients.emplace_back(ingredient);
        }
        void printSandwich(){
            for(Ingredient *x: ingredients){
                std::cout<< x->name() << " : "<< x->calories() <<" : "<< x->cost() << std::endl;
            }
        }
        void getTotalCalories(){
            int totalCalories = 0;
            for(Ingredient *x: ingredients){
                totalCalories += x->calories();
            }

            std::cout<<"Total Calories: "<<totalCalories<<std::endl;
        }
};

// x{20} ---> initializer_rest
class SandwichBuilder{
    public:
    static Sandwich readyMade(){
        // hardcoding ingredients, not acceptable
        Sandwich sandwich;
        sandwich.addIngredients(new Bage1);
        sandwich.addIngredients(new Cheese);
        sandwich.addIngredients(new Meat);

        return sandwich;
    }

    static Sandwich build(Sandwich& s, Ingredient* ingredient){
        s.addIngredients(ingredient);
        return s;
    }
};



int main(){
    std::cout<<"Sandwich Builder"<<std::endl;
    Sandwich custom;
    SandwichBuilder::build(custom, new Bage1);
    SandwichBuilder::build(custom, new Cheese);

    custom.getTotalCalories();
    custom.printSandwich();

    std::cout<<"Ready Made:\n";
    Sandwich myself = SandwichBuilder::readyMade();
    myself.getTotalCalories();
    myself.printSandwich();
}