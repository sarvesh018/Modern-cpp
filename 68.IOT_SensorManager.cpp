//
//  main.cpp
//  IOT_SensorManager
//
//  Created by Sathya Babu on 19/02/24.
//

#include <iostream>
#include <memory>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>
#include <random>
#include <future>


// Function to generate a random value within a specified range
template <typename T>
T generateRandomValue(T min, T max) {
     std::random_device rd;  // static
     std::mt19937 gen(rd());
    std::uniform_int_distribution<T> dis(min, max);
    return dis(gen);
}
// Abstract class representing a sensor
// maintain a state machine ion sensors..
class Sensor {
public:
    virtual ~Sensor() = default;
    virtual void readData() = 0;
};

// Engine RPM sensor
class RPM_Sensor : public Sensor {
public:
    void readData() override {
        // Simulate reading RPM data
        int rpm = generateRandomValue(1000, 7000); // RPM range: 1000 - 7000
        std::cout << "Engine RPM: " << rpm << " RPM" << std::endl;
    }
};

// Oil pressure sensor
class OilPressure_Sensor : public Sensor {
public:
    void readData() override {
        // Simulate reading oil pressure data
        double oilPressure = generateRandomValue(10, 100); // Pressure range: 10 - 100 psi
        std::cout << "Oil Pressure: " << oilPressure << " psi" << std::endl;
    }
};

class SensorManager{
    private :
    std::vector< std::shared_ptr< Sensor >> sensors ;
    std::mutex mutex ;
    
    public :
    // add as a composite.. Engine with child as oil , petrol, coolent ...
    void addSensor( std::shared_ptr< Sensor > sensor) {
        
        sensors.emplace_back( sensor );
    }
    
    void readSensorData(){
        while( true ){
            std::this_thread::sleep_for(std::chrono::seconds( 1 ));
            
            std::lock_guard< std::mutex> lock( mutex);
            
            // read the data
            for(  const auto& sensor1 : sensors ){      //                sensor->readData();
                sensor1->readData();
            }
            
        }  
    }
};

int main(){
    
//    SensorManager manager ;
//    manager.addSensor(std::shared_ptr< RPM_Sensor >());
//    manager.addSensor(std::shared_ptr< OilPressure_Sensor >());
//    std::thread sensorThread( &SensorManager::readSensorData,&manager);
//    sensorThread.join();
//    
    
    // phase II
   // Start reading sensor data asynchronously
   SensorManager manager2;

      // Create sensors and add them to the manager
      manager2.addSensor(std::make_shared<RPM_Sensor>());
      manager2.addSensor(std::make_shared<OilPressure_Sensor>());

      // Start reading sensor data asynchronously
      std::future<void> sensorFuture2 = std::async(std::launch::async, [ &manager2 ] { manager2.readSensorData(); });

      // Wait for sensor data reading to complete
      sensorFuture2.wait();
    
}
