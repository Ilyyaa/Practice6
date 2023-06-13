#include "Appartment.h"
#include <iostream>
using namespace TAX_RATES;

void Appartment::tostr() {
	cout << " вартира ";
	cout << getSquare() << " кв. метров." << endl;
}

Appartment::Appartment(unsigned int worth, double square) {
	this->square = square;
	setWorth(worth);
}

double Appartment::calculateTax() {
	double wor = getWorth();
	if (this->square <= LIMIT_APPARTMENT_SQUARE) {
		wor *= APPARTMENT_TAX;
		wor += IncomeTax();
		return wor;
	}
	else {
		wor *= APPARTMENT_LUXURY_TAX;
		wor += IncomeTax();
		return wor;
	}
}

void Appartment::fromJson(nlohmann::json json) {
	nlohmann::json jAppartment = json["Appartment"].get<nlohmann::json>();
	square = jAppartment["square"].get<double>();
	setWorth(jAppartment["worth"].get<double>());
}

nlohmann::json Appartment::toJson() {
	json appart_tax;
	appart_tax["tax"] = calculateTax();
	json appart;
	appart["Appartment"] = appart_tax;
	return appart;
}