#include <iostream>

// 1c2f

class Animal{
    private:
        const std::string type;
    public:

        // const constructor
        Animal() : type("Animal"){}

        // phase 1
        // std::string getType(){
        //     return type;
        // }

        // phase 2
        // virtual std::string getType(){
        //     return type;
        // }

        // phase 3
        virtual std::string getType() = 0;
};

//   ff00          1c2f
class Dog: public Animal{
    private:
        std::string type;
    public:
        Dog(): type("Dog"){}
        std::string getType(){
            return type;
        }
};

//     ffee         1c2f
class Cat: public Animal{
    private:
        std::string type;
    public:
        Cat() : type("Cat"){}
        std::string getType(){
            return type;
        }
};


void printAnimalType(Animal *animal){
    std::cout<<animal->getType()<<std::endl;
}


// Real time use case
class Brew{
    public:
        void boilWater(){
            std::cout<<"Boil Water"<<std::endl;
        }
        void boilMilk(){
            std::cout<<"Boil Milk"<<std::endl;
        }
        void pourItInMug(){
            std::cout<<"Pour it in mug"<<std::endl;
        }

        virtual void AddCondiments1() = 0;
        virtual void AddCondiments2() = 0;
        virtual void AddCondiments3() = 0;

        // execute function for ordering
        void execute(){
            boilWater();
            boilMilk();
            pourItInMug();
            AddCondiments1();
            AddCondiments2();
            AddCondiments3();
        }
};

class Tea: public Brew{
    public:
        void AddCondiments1() override{
            std::cout<<"Steep the tea bag"<<std::endl;
        }
        void AddCondiments2() override{
            std::cout<<"Add Sugar"<<std::endl;
        }
        void AddCondiments3() override{
            std::cout<<"Add Lime"<<std::endl;
        }
};

class Coffee: public Brew{
    public:
        void AddCondiments1() override{
            std::cout<<"Steep the tea bag"<<std::endl;
        }
        void AddCondiments2() override{
            std::cout<<"Add Sugar"<<std::endl;
        }
        void AddCondiments3() override{
            std::cout<<"Add Lime"<<std::endl;
        }
};

int main(){
    std::cout<<"Virtual Function!"<<std::endl;

    // Phase 1
    // not allowed when its a pure virtual function
    // Animal* animal = new Animal(); // 1c2f

    Animal* dog = new Dog();
    Animal* cat = new Cat();

    std::cout<<dog->getType()<<std::endl;
    std::cout<<cat->getType()<<std::endl;

    // standalone function
    printAnimalType(dog);
    printAnimalType(cat);

    std::cout<<std::endl;
    Brew *brew = new Tea;
    // Brew *brew1 = new Coffee();

    brew->pourItInMug();
    brew->AddCondiments3();
    brew->boilMilk();
    brew->AddCondiments2();
    brew->boilWater();
    brew->AddCondiments1();

    std::cout<<"\nAfter execute function: "<<std::endl;
    brew->execute();

    Brew* array[]{new Tea(), new Coffee()};
    for(int i=0; i<2; i++){
        array[i]->execute();
    }
    return 0;
}