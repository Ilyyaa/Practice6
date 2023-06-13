#include "CountryHouse.h"
#include <iostream>
#include "json.hpp"

using namespace TAX_RATES;
using namespace nlohmann;

void CountryHouse::tostr() {
	cout << "Удаленность дома от города: ";
	cout << getDistance() << " км." << endl;
}

CountryHouse::CountryHouse(unsigned int worth, unsigned int distance_from_city) {
	this->distance_from_city = distance_from_city;
	setWorth(worth);
}

double CountryHouse::calculateTax() {
	double wor = getWorth();
	if (this->distance_from_city <= LIMIT_DISTANCE_FROM_CITY) {
		wor *= APPARTMENT_TAX;
		wor += IncomeTax();
		return wor;
	}
	else {
		wor *= COUNTRY_HOUSE_TAX;
		wor += IncomeTax();
		return wor;
	}
}

void CountryHouse::fromJson(nlohmann::json json) {
	nlohmann::json jHouse = json["CountryHouse"].get<nlohmann::json>();
	distance_from_city = jHouse["distance_from_city"].get<unsigned int>();
	setWorth(jHouse["worth"].get<double>());
}

nlohmann::json CountryHouse::toJson() {
	json house_tax;
	house_tax["tax"] = calculateTax();
	json house;
	house["House"] = house_tax;
	return house;
}
