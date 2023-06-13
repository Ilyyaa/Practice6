#pragma once
#include "Property.h"

class CountryHouse : public Property {
private:
	unsigned int distance_from_city;
public:
	CountryHouse(unsigned int worth, unsigned int distance_from_city = 0);
	double calculateTax() override;
	void tostr() override;
	double getDistance() { return distance_from_city; }
	void fromJson(json json) override;
	json toJson() override;
};

