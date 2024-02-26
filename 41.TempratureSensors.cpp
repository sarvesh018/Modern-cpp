//
//  main.cpp
//  TempratureSensorBasicCode
//
//  Created by Sathya Babu on 08/02/24.
//

#include <iostream>
#include <vector>
#include <functional>
#include<chrono>
#include <thread>

class TemperatureSensor {
public:
    using CallbackFunction = std::function<void(double)>;

    void setTemperature(double temperature) {
        if (temperature_ != temperature) {
            temperature_ = temperature;
            notifyObservers();
        }
    }

    void registerCallback(const CallbackFunction& callback) {
        callbacks_.push_back(callback);
    }

private:
    void notifyObservers() {
        for (auto& callback : callbacks_) {
            callback(temperature_);
        }
    }

    double temperature_ = 0.0;
    std::vector<CallbackFunction> callbacks_;
};

class Display {
public:
    void update(double temperature) {
        std::cout << "Current temperature is: " << temperature << std::endl;
    }
};

int main() {
    TemperatureSensor sensor;
    Display display;

    // Registering a lambda function as a callback
    sensor.registerCallback([&display](double temperature) {
        display.update(temperature);
    });

    // Changing temperature will notify the observers
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Delay for 1 second
    sensor.setTemperature(20.0);
    std::this_thread::sleep_for(std::chrono::seconds(5)); // Delay for 1 second
    sensor.setTemperature(25.0);
    std::this_thread::sleep_for(std::chrono::seconds(3)); // Delay for 1 second
    sensor.setTemperature(30.0);

    return 0;
}