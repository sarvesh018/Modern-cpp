//
//  main.cpp
//  ObserverEngineSensors
//
//  Created by Sathya Babu on 21/02/24.
//
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <mutex>

// Observer interface
class Observer {
public:
    virtual void onDataChanged(const std::string& sensorName, int newValue) = 0;
};

// EngineManager that receives data from sensors and notifies observers
class EngineManager {
private:
    std::map<std::string, int> sensorData; // Map to store sensor data
    std::vector<std::shared_ptr<Observer>> observers;
    std::mutex mutex;
    bool engineRunning; // Flag to indicate engine running state

public:
   
    EngineManager() : engineRunning(false) {}

   
    void addObserver(const std::shared_ptr<Observer>& observer) {
        observers.push_back(observer);
    }

    
    void startEngine() {
        std::lock_guard<std::mutex> lock(mutex);
        engineRunning = true;
        std::cout << "Engine started." << std::endl;
    }

   
    void stopEngine() {
        std::lock_guard<std::mutex> lock(mutex);
        engineRunning = false;
        std::cout << "Engine stopped." << std::endl;
    }

    //  Receive data from sensors and notify observers if data changes
    void onDataReceived(const std::string& sensorName, int newValue) {
        std::lock_guard<std::mutex> lock(mutex);
        if (sensorData[sensorName] != newValue) { // Check if data has changed
            sensorData[sensorName] = newValue; // Update sensor data
            notifyObservers(sensorName, newValue);
        }
    }

private:
   
    void notifyObservers(const std::string& sensorName, int newValue) {
        for (const auto& observer : observers) {
            observer->onDataChanged(sensorName, newValue);
        }
    }
};

// Concrete observer (e.g., dashboard) that displays data
class Dashboard : public Observer {
public:
    // Method to display data when it changes
    void onDataChanged(const std::string& sensorName, int newValue) override {
        std::cout << "Dashboard received updated data from sensor '" << sensorName << "': " << newValue << std::endl;
    }
};

// Sensor class representing various sensors
class Sensor {
private:
    EngineManager& engineManager; // Composed EngineManager
    std::string name; // Sensor name

public:
   
    Sensor(const std::string& sensorName, EngineManager& manager) : name(sensorName), engineManager(manager) {}

   
    void sendData(int value) {
       
        std::cout << "Sensor '" << name << "' sending data: " << value << std::endl;

        engineManager.onDataReceived(name, value);
    }
};


class PetrolTank {
private:
    int petrolLevel;
    EngineManager& engineManager;

public:
   
    PetrolTank(EngineManager& manager) : petrolLevel(100), engineManager(manager) {}

   
    int getPetrolLevel() const {
        return petrolLevel;
    }

   
    void consumePetrol() {
        petrolLevel -= 10;
        if (petrolLevel <= 10) {
            engineManager.onDataReceived("Petrol", petrolLevel); // Notify EngineManager when petrol level is low
        }
    }
};

// Car class that composes EngineManager and controls the engine
class Car {
//private:
public:
    EngineManager engineManager;
    PetrolTank petrolTank;

public:
    // Constructor
    Car() : petrolTank(engineManager) {
        engineManager.addObserver(std::make_shared<Dashboard>()); // Compose dashboard observer to EngineManager
    }

   
    void startEngine() {
        engineManager.startEngine();
    }

   
    void stopEngine() {
        engineManager.stopEngine();
    }

    
    void checkPetrolLevel() {
        petrolTank.consumePetrol();
    }
};

int main() {
    Car car;

    // Create and register sensors
    Sensor rpmSensor("RPM", car.engineManager);
    Sensor tempSensor("Temperature", car.engineManager);

   
    car.startEngine();

   
    rpmSensor.sendData(20);
    tempSensor.sendData(90);

    // Check petrol level
    car.checkPetrolLevel();

    return 0;
}

/*
 Sensor 'RPM' sending data: 20
 Sensor 'Temperature' sending data: 70
 Dashboard received updated data from sensor 'Temperature': 1
 Program ended with exit code: 0
 */
