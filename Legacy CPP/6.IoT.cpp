//3. compose IoT to tier, fuel tank...display the details to car dashboard

#include <iostream>

// abstract class tier
class Tier{
	protected:
	float tierPressure;
	public:
	virtual void setPressure(float pressure) = 0;
	virtual float getPressure() = 0;
};

// abstract class FuelTank
class FuelTank{
	protected:
	int fuelCapacity;
	public:
	virtual void setFuelCapacity(float capacity) = 0;
	virtual int getFuelCapacity() = 0;
};

// IoT1 sense tier pressure from tier
class IoT1 : public Tier{
	void setPressure(float pressure) override {
		tierPressure = pressure;
	}
	float getPressure() override{
		return tierPressure;
	}
};


// IoT2 sense fuel capacity from FuelTank
class IoT2 : public FuelTank{
	void setFuelCapacity(float capacity){
		fuelCapacity = capacity;
	}
	int getFuelCapacity(){
		return fuelCapacity;
	}
};

// Takes input from IoT1 and IoT2 and display it to user
class DashBoard{
	public:
	void showData(Tier* t, FuelTank* f){
		std::cout<<"Tier Pressure: "<<t->getPressure()<<std::endl;
		std::cout<<"Fuel Capacity: "<<f->getFuelCapacity()<<std::endl;
	}
};


int main(){
	Tier* iot1 = new IoT1();
	FuelTank* iot2 = new IoT2();

	iot1->setPressure(56.89);
	iot2->setFuelCapacity(80);

	DashBoard data;
	data.showData(iot1, iot2);
}

