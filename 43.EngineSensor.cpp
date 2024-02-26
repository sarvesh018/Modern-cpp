#include <iostream>
#include <variant>
#include <vector>
#include <type_traits>

// Define the types for different sensors
struct FuelSensor { float fuelLevel; };
struct CoolingSensor { float coolingTemperature; };
struct SpeedSensor { float speed; };

// Define the components of the car
struct Engine {
    std::vector<FuelSensor> fuelSensors;
};

struct AC {
    std::vector<CoolingSensor> coolingSensors;
};

struct Wheels {
    std::vector<SpeedSensor> speedSensors;
};

// Define a variant to hold different component types
using Component = std::variant<Engine, AC, Wheels>;

// Dashboard to display data to the user
class Dashboard {
public:
    void displayFuelLevel(float fuelLevel) const {
        std::cout << "Fuel Level: " << fuelLevel << " gallons" << std::endl;
    }

    void displayCoolingTemperature(float temperature) const {
        std::cout << "Cooling Temperature: " << temperature << " °C" << std::endl;
    }

    void displaySpeed(float speed) const {
        std::cout << "Speed: " << speed << " mph" << std::endl;
    }

    // Function to display data from sensors on the dashboard
    void displayData(const Component& component) const {
        std::visit([&](auto&& comp) {
            using T = std::decay_t<decltype(comp)>;
            if constexpr (std::is_same_v<T, Engine>) {
                for (const auto& sensor : comp.fuelSensors) {
                    displayFuelLevel(sensor.fuelLevel);
                }
            } else if constexpr (std::is_same_v<T, AC>) {
                for (const auto& sensor : comp.coolingSensors) {
                    displayCoolingTemperature(sensor.coolingTemperature);
                }
            } else if constexpr (std::is_same_v<T, Wheels>) {
                for (const auto& sensor : comp.speedSensors) {
                    displaySpeed(sensor.speed);
                }
            }
        }, component);
    }
};

int main() {
    // Create instances of car components
    Engine engine{{ {50.0f}, {40.0f}, {60.0f}, {55.0f}, {45.0f} }};
    AC ac{{ {20.0f}, {22.0f} }};
    Wheels wheels{{ {60.0f}, {65.0f}, {70.0f} }};

    using Data = std::variant<Engine, AC, Wheels>;
    std::vector<Data> data = {engine, ac, wheels};

    // Create a dashboard
    Dashboard dashboard;

    // Display data from sensors on the dashboard
    for(auto& d: data){
        std::visit([&](auto& obj){
            dashboard.displayData(obj);
        } ,d);
    }
    // dashboard.displayData(engine);
    // dashboard.displayData(ac);
    // dashboard.displayData(wheels);

    return 0;
}
