#pragma once
#include "Property.h"

class Car : public Property {
private:
	double horsepower;
public:
	Car(unsigned int worth, double horsepower = 0);
	double calculateTax() override;
	void tostr() override;
	double getHorsepower() { return horsepower; }
	void fromJson(json json) override;
	json toJson() override;
};
