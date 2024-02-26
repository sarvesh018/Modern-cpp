#include<bits/stdc++.h>
 
 
class Ingredient {
public:
    virtual std::string name() = 0;
    virtual int calories() = 0;
    virtual int cost() = 0;
    virtual ~Ingredient() = default;
};
 
class Bread : public Ingredient {
public:
    virtual std::string name() = 0;
    virtual int calories() = 0;
    virtual int cost() = 0;
};
 
class bagel : public Bread {
public:
    std::string name() override {
        return "Bagel";
    }
 
    int calories() override {
        return 250;
    }
 
    int cost() override {
        return 20;
    }
};
 
class bun : public Bread {
public:
    std::string name() override {
        return "Bun";
    }
 
    int calories() override {
        return 150;
    }
 
    int cost() override {
        return 10;
    }
};
 
class filling : public Ingredient {
public:
    virtual std::string name() = 0;
    virtual int calories() = 0;
    virtual int cost() = 0;
};
 
class creamcheese : public filling {
public:
    std::string name() override {
        return "Cream cheese";
    }
 
    int calories() override {
        return 350;
    }
 
    int cost() override {
        return 100;
    }
};
 
class salmon : public filling {
public:
    std::string name() override {
        return "Salmon ";
    }
 
    int calories() override {
        return 270;
    }
 
    int cost() override {
        return 150;
    }
};
 
class Sandwich {
private:
    std::vector<Ingredient*> ingredients;
 
public:
    void addIngredients(Ingredient* ingredient) {
        ingredients.emplace_back(ingredient);
    }
 
    void getSandwich() {
        for (Ingredient* i : ingredients) {
            std::cout << i->name() << " : " << i->calories() << " kCal, " << i->cost() << " Cost" << std::endl;
        }
    }

    void getCalories() {
        int totalCalories = 0;
        for (Ingredient* i : ingredients) {
            totalCalories += i->calories();
        }
        std::cout << "Total Calories: " << totalCalories << std::endl;
    }

    int getCostOfSandwich() {
        int totalCost = 0;
        for (Ingredient* i : ingredients) {
            totalCost += i->cost();
        }
        return totalCost;
    }
};
 
class IngredientProvider {
public:
    virtual Ingredient* getBageIngredient() = 0;
};
 
class DynamicIngredientProvider : public IngredientProvider {
public:
    Ingredient* getBageIngredient() override {
        std::cout << "Enter 1 for Bage1, 2 for Bage2: ";
        int choice;
        std::cin >> choice;
 
        if (choice == 1) {
            return new bagel();
        } else if (choice == 2) {
            return new bun();
        } else {
            std::cout << "Invalid choice. Returning default ingredient bagel." << std::endl;
            return new bagel(); // Default to bagel
        }
    }
};
 
class SandwichBuilder {
public:
    static Sandwich readyMade() {
        Sandwich sandwich;
        sandwich.addIngredients(new bagel());
        sandwich.addIngredients(new salmon());
        sandwich.addIngredients(new creamcheese());
 
        return sandwich;
    }
 
    static Sandwich build(Sandwich& s, Ingredient* ingredient) {
        s.addIngredients(ingredient);
        return s;
    }
 
    static Sandwich buildWithProvider(Sandwich& s, IngredientProvider* provider) {
        Ingredient* ingredient = provider->getBageIngredient();
        s.addIngredients(ingredient);
        return s;
    }
};
//----------------------------Visitor Auditor--------------------------
// modern c++ breaks the double dispatching mechanism
class AuditorSandwichVisitor{
    public:
        void operator()(Sandwich sandwich){
        // use proxy as a wrapper to sandwich to avoid giving access to unrequierd member functions and private vari.
            sandwich.getSandwich();
            sandwich.getCostOfSandwich();
        }
};

/*-----------------------------  VISITOR  ------------------------------*/
 
int main() {
    std::cout << "Sandwich Builder!\n\n";
 
    Sandwich custom;
    SandwichBuilder::build(custom, new bun());
    SandwichBuilder::build(custom, new creamcheese());
    std::cout << "Customised Sandwich\n\n";
    // custom.getSandwich();
    // custom.getCalories();
 
    DynamicIngredientProvider dynamicProvider;
    SandwichBuilder::buildWithProvider(custom, &dynamicProvider);
 
    std::cout << "Dynamic Customised Sandwich\n\n";
    // custom.getSandwich();
    // custom.getCalories();
 
    Sandwich offTheShelf = SandwichBuilder::readyMade();
 
    std::cout << "Ready-made sandwich " << std::endl;
    // offTheShelf.getSandwich();

    //------------------------using visitor and visitable-------------------
    // SOLID (D) --> Dependency inversion principle
    // VISITOR
    using SandwichType = std::variant<Sandwich>;
    std::vector<SandwichType> mySandwiches{custom, offTheShelf};

    AuditorSandwichVisitor auditorsVisit;
    auto visitSandWich = [&](const auto& sandwichSeq){
        std::visit(auditorsVisit, sandwichSeq);
    };
        //auditorsVisit( Sandwich );
    for(const auto& sandwichSequence: mySandwiches){

        visitSandWich( sandwichSequence );

        // std::visit([&](){}, sandwichSequence);
    }
 
    return 0;
}
