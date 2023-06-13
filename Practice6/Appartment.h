#pragma once
#include "Property.h"

class Appartment : public Property {
private:
	double square;
public:
	Appartment(unsigned int worth, double square = 0);
	double calculateTax() override;
	void tostr() override;
	double getSquare() { return square; }
	void fromJson(json json) override;
	json toJson() override;
};

