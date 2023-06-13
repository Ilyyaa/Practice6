#include "Car.h"
#include <iostream>
using namespace TAX_RATES;

void Car::tostr() {
	cout << "Машина ";
	cout << getHorsepower() << " лошадиных сил." << endl;
}

Car::Car(unsigned int worth, double horsepower) {
	this->horsepower = horsepower;
	setWorth(worth);
}

double Car::calculateTax() {
	double wor = getWorth();
	if (this->horsepower < LOW_HORSEPOWER) {
		wor *= CAR_TAX;
		wor += IncomeTax();
		return wor;
	}
	else {
		if (this->horsepower > HIGH_HORSEPOWER) {
			wor *= CAR_LUXURY_TAX;
			wor += IncomeTax();
			return wor;
		}
		else {
			wor *= CAR_TRUCK_TAX;
			wor += IncomeTax();
			return wor;
		}
	}
}

void Car::fromJson(nlohmann::json json) {
	nlohmann::json jCar = json["Car"].get<nlohmann::json>();
	horsepower = jCar["horsepower"].get<double>();
	setWorth(jCar["worth"].get<double>());
}

nlohmann::json Car::toJson() {
	json car_tax;
	car_tax["tax"] = calculateTax();
	json car;
	car["Car"] = car_tax;
	return car;
}