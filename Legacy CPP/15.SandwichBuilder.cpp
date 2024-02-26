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

// SERVICE PROVIDER TO SANDWICH
// IT WILL DYNAMICALLY PROVIDE FILLINGS OF SANDWICH TI SANDWICH BUILDER
class ServeSandwich{
    public:
        Ingredient* ingredients;

        Ingredient* getIngredients(Ingredient* ingredient){
            if(ingredient->name() == "Cheese"){
                ingredients = new Cheese; 
            }
            else if(ingredient->name() == "Meat"){
                ingredients = new Meat;
            }
            else if(ingredient->name() == "Bage1"){
                ingredients = new Bage1;
            }
            else if(ingredient->name() == "Bage2"){
                ingredients = new Bage2;
            }
            return ingredients;
        }
};

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

    // providing fillings to sandwich
    static Sandwich serve(Sandwich& s, Ingredient* filling){
        ServeSandwich serveSandwich;
        s.addIngredients(serveSandwich.getIngredients(filling));

        return s;
    }
};



int main(){
    std::cout<<"Sandwich Builder"<<std::endl;
    Sandwich custom;
    // dynamically providing fillings to sandwich
    Filling* filling1 = new Meat;
    Filling* filling2 = new Cheese;
    SandwichBuilder::serve(custom, filling1);
    SandwichBuilder::serve(custom, filling2);

    custom.getTotalCalories();
}