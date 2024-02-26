#include <iostream>
#include <variant>
#include <memory>
#include <vector>

//----------------------------------Visitor-----------------------------------

class VisitorController {
public:
    float fuel;
    int8_t battery;

    VisitorController() = default;
    VisitorController(float f, int8_t b) : fuel(f), battery(b) {}

    using IOT = std::variant<float, int8_t>;
    std::vector<IOT> check = {fuel, battery};

    bool checkFuel() {
        bool flag = false;
        std::visit([&](auto &fuel) {
            fuel -= 10;
            if (fuel > 15) {
                flag = true;
            }
        }, check[0]);
        return flag;
    }

    bool checkBattery() {
        bool flag = false;
        std::visit([&](auto &battery) {
            battery--;
            if (battery > 50) {
                flag = true;
            }
        }, check[1]);
        return flag;
    }

    float getFuel() const {
        return fuel;
    }

    int8_t getBattery() const {
        return battery;
    }
};

// ------------------------ Abstraction Layer CarState ----------------------

class CarState {
public:
    virtual ~CarState() = default;
    virtual void startCar() = 0;
    virtual void stopCar() = 0;
    virtual void accelerate() = 0;
    virtual void applyBrake() = 0;
};

// ------------------------- Concrete CAR Class ------------------------------------

class Car {
    std::shared_ptr<CarState> carState;
    std::shared_ptr<VisitorController> vc;

public:
    Car(std::shared_ptr<VisitorController> vc) : vc(vc) {
        carState = std::make_shared<TurnOff>(this);
    }

    void setCarState(std::shared_ptr<CarState> state) {
        carState = std::move(state);
    }

    void startCar() {
        carState->startCar();
    }

    void stopCar() {
        carState->stopCar();
    }

    void accelerate() {
        carState->accelerate();
    }

    void applyBrake() {
        carState->applyBrake();
    }

    bool checkFuel() {
        return vc->checkFuel();
    }

    bool checkBattery() {
        return vc->checkBattery();
    }

    float getFuel() const {
        return vc->getFuel();
    }

    int8_t getBattery() const {
        return vc->getBattery();
    }
};

// ------------------------States-------------------------

// TURNOFF STATE
class TurnOff : public CarState {
    Car *newState;

public:
    TurnOff(Car *currentState) : newState(currentState) {
        std::cout << "Car is in turnoff state" << std::endl;
    }

    void startCar() override;

    void stopCar() override {
        std::cout << "Car is not moving" << std::endl;
    }

    void accelerate() override {
        std::cout << "First turn on the car" << std::endl;
    }

    void applyBrake() override {
        std::cout << "Car is not moving" << std::endl;
    }
};

// TURNON STATE
class TurnOn : public CarState {
    Car *newState;

public:
    TurnOn(Car *currentState) : newState(currentState) {
        std::cout << "Car Started !!" << std::endl;
        std::cout << "Fuel: " << newState->getFuel() << std::endl;
        std::cout << "Battery: " << newState->getBattery() << " %" << std::endl;
    }

    void startCar() override {
        std::cout << "Car is already started" << std::endl;
    }

    void stopCar() override;

    void accelerate() override;

    void applyBrake() override;
};

// RUNNING STATE
class Running : public CarState {
    Car *newState;

public:
    Running(Car *currentState) : newState(currentState) {
        std::cout << "Car is running" << std::endl;
    }

    void startCar() override {
        std::cout << "Car is already started" << std::endl;
    }

    void stopCar() override;

    void accelerate() override;

    void applyBrake() override;
};

// STOP STATE
class Stop : public CarState {
    Car *newState;

public:
    Stop(Car *currentState) : newState(currentState) {
        std::cout << "Car stopped!" << std::endl;
    }

    void startCar() override {
        std::cout << "Car is already started" << std::endl;
    }

    void stopCar() override {
        std::cout << "Car is not moving" << std::endl;
    }

    void accelerate() override;

    void applyBrake() override {
        std::cout << "Car is not moving" << std::endl;
    }
};

// ------TURNOFF------
void TurnOff::startCar() {
    if (newState->checkBattery()) {
        newState->setCarState(std::make_shared<TurnOn>(newState));
    } else {
        std::cout << "Battery is low" << std::endl;
    }
}

// --------TURNON-------
void TurnOn::stopCar() {
    newState->setCarState(std::make_shared<TurnOff>(newState));
}

void TurnOn::accelerate() {
    if (newState->checkFuel()) {
        newState->setCarState(std::make_shared<Running>(newState));
    } else {
        std::cout << "You are running out of fuel" << std::endl;
    }
}

void TurnOn::applyBrake() {
    newState->setCarState(std::make_shared<Stop>(newState));
}

// ----RUNNING------
void Running::stopCar() {
    newState->setCarState(std::make_shared<TurnOff>(newState));
}

void Running::accelerate() {
    if (newState->checkFuel()) {
        newState->setCarState(std::make_shared<Running>(newState));
    } else {
        std::cout << "You are running out of fuel " << std::endl;
    }
}

void Running::applyBrake() {
    newState->setCarState(std::make_shared<Stop>(newState));
}

//------STOP-------
void Stop::accelerate() {
    if (newState->checkFuel()) {
        newState->setCarState(std::make_shared<Running>(newState));
    } else {
        std::cout << "You are running out of fuel" << std::endl;
    }
}

// -----------------------MAIN---------------------

int main() {
    std::shared_ptr<VisitorController> vc = std::make_shared<VisitorController>(40.0f, 100);
    std::shared_ptr<Car> car = std::make_shared<Car>(vc);

    car->startCar();
    car->accelerate();
    car->accelerate();
    car->applyBrake();
    car->accelerate();
    car->stopCar();

    return 0;
}
