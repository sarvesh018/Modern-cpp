#include <iostream>
#include <type_traits>
#include <functional>
#include <variant>

// concept and requires to check type of incoming data should be float
template<typename T>    //*M (template<typename T> )
concept MandateData = requires(T t){
    requires std::is_same_v<decltype(t), float>;
};

class Car{
    public:
    using IOT = std::function<void()>;        
        // set engine iot data
        // taking data as rValue and message as lValue

    // incoming data should be float otherwise it will throw compile time error
    template<MandateData Ts>
    IOT setData(const Ts&& data, const std::string& message, const std::string& component){
        auto&& iotData = [=](){
            std::cout<<component<<std::move(data)<<"\t : \t"<<message<<std::endl;    //*M (std::cout)
            return message;
        }; 
        return iotData;   // returning callback function
    }

    template<MandateData Ts>
    constexpr void setEngineData(const Ts&& data, const std::string& message) noexcept { //*M (noexcept)

        engineData.emplace_back(setData(static_cast<float>(data), message, "Engine details\t -->\t"));
    }

    // set ac iot data
    template<MandateData Ts>
    void setACData(const Ts&& data, const std::string& message) noexcept { //*M (noexcept)
        AC.emplace_back(setData(static_cast<float>(data), message, "AC details\t -->\t"));
    }

    // set petrol tank iot data
    template<MandateData Ts>
    void setPetrolTankData(const Ts&& data, const std::string& message) noexcept { //*M (noexcept)
        pertrolTank = std::move(setData(static_cast<float>(data), message, "Petrol details\t --> \t"));
    }

    // set motor iot data
    template<MandateData Ts>
    void setMotorData(const Ts&& data, const std::string& message) noexcept { //*M (noexcept)
        motor = std::move(setData(static_cast<float>(data), message, "Motor details\t --> \t"));
    }

    // set temperature iot data
    template<MandateData Ts>
    void setTemperatureData(const Ts&& data, const std::string& message) noexcept { //*M (noexcept)
        temprature = std::move(setData(static_cast<float>(data), message, "Temp. details\t --> \t"));
    }

    public:
        std::vector<IOT> engineData;
        IOT pertrolTank;
        std::vector<IOT> AC;    
        IOT motor;
        IOT temprature;
};


// View class to print the details shown on the dashboard
class View{
    public:
        using IOT = std::function<void()>;
        using Variants = std::variant<std::vector<IOT>, IOT>;

        // taking data as lVlaue
        void printDetails(const std::vector<IOT>& data){
            for(const auto& printData: data){
                printData();
            }
            std::cout<<std::endl;
        }

        // taking data as rValue
        void printDetails(const IOT& data){
            data();
            std::cout<<std::endl;
        }
};

// Dashboard class to recieve inputs from iot
// Dashboard ---> acting as controller
class Dashboard{
    private:
        Car& carData;
        View& view;
    public:
        Dashboard(Car& c, View& v) : carData(c), view(v){}

        // Observer to print the data
        template<typename T, typename U>
        void observer(const T& observe, U& value){
            observe(value);
            view.printDetails(carData.AC);
            view.printDetails(carData.engineData);
            view.printDetails(carData.pertrolTank);
            view.printDetails(carData.motor);
            view.printDetails(carData.temprature);            
        }                                
};

int main(){
    try{
        Car car;
        View view;
        Dashboard dashboard(car, view);

        // setting engine details through iot
        car.setEngineData(23.9f, "Pump Data");
        car.setEngineData(41.34f, "Oil Level");
        car.setEngineData(90.0f, "Temprature");
        car.setEngineData(56.93f, "Efficienfy");
        car.setEngineData(67.12f, "Fuel Usage");

        // setting ac details through iot
        car.setACData(45.31f, "Colling Speed");
        car.setACData(12.00f, "Internal Temprature");

        // setting petrol tank data
        car.setPetrolTankData(45.08f, "Liter");

        // setting motor data
        car.setMotorData(125.89f, "RPM");
        car.setTemperatureData(12.00f, "Degree");

        // display details to driver on dashboard
        dashboard.observer(
                [](std::string name){
                    std::cout<<"\nObserver Name: "<<name<<std::endl;
                }, "Sarvesh\n"
        );

        // update data
        car.setMotorData(234.32f, "RPM");
        car.setPetrolTankData(30.08f, "Liter");
        car.setTemperatureData(10.00f, "Degree");

        dashboard.observer(
                [](std::string name){
                    std::cout<<"\nObserver Name: "<<name<<std::endl;
                }, "Observer 2\n"
        );
    }
    catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
    }
}