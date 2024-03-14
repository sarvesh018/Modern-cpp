#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

// Forward declaration of Observer interface
class Observer;

// Subject interface
class Subject {
public:
    virtual ~Subject() {}
    virtual void attach(std::shared_ptr<Observer> observer) = 0;
    virtual void detach(std::shared_ptr<Observer> observer) = 0;
    virtual void notify() = 0;
};

// Observer interface
class Observer {
public:
    virtual ~Observer() {}
    virtual void update(const std::string& data) = 0;
};

// Concrete subject representing a sensor
class Sensor : public Subject {
private:
    std::vector<std::shared_ptr<Observer>> observers;
    std::string data;
public:
    void attach(std::shared_ptr<Observer> observer) override {
        observers.push_back(observer);
    }

    void detach(std::shared_ptr<Observer> observer) override {
        auto it = std::find_if(observers.begin(), observers.end(), [&](const std::shared_ptr<Observer>& ptr) {
            return ptr.get() == observer.get();
        });
        if (it != observers.end()) {
            observers.erase(it);
        }
    }


    void notify() override {
        for (const auto& observer : observers) {
            observer->update(data);
        }
    }

    void setData(const std::string& newData) {
        data = newData;
        notify();
    }
};

// Concrete observer representing a monitoring component
class MonitoringComponent : public Observer {
public:
    void update(const std::string& data) override {
        std::cout << "MonitoringComponent received update: " << data << std::endl;
    }
};

int main() {
    // Create sensor and monitoring component
    std::shared_ptr<Sensor> sensor = std::make_shared<Sensor>();
    std::shared_ptr<MonitoringComponent> monitoringComponent = std::make_shared<MonitoringComponent>();

    // Attach monitoring component to sensor
    sensor->attach(monitoringComponent);

    // Simulate data updates from sensor
    sensor->setData("Temperature: 25C");
    sensor->setData("Motion detected");

    // Detach monitoring component from sensor
    sensor->detach(monitoringComponent);

    // Simulate another data update (should not be received by monitoring component)
    sensor->setData("Window opened");

    return 0;
}
