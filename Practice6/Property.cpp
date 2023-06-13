#include "Property.h"
#include <sstream>
#include <iostream>
#include "json.hpp"
using namespace nlohmann;
using namespace TAX_RATES;
using namespace std;

Property::~Property() {}

double Property::calculateTax() {
	return 0;
}

double Property::IncomeTax() {
	return this->worth * 0.13;
}

unsigned int Property::getWorth() {
	return worth;
}

void Property::setWorth(unsigned int worth) {
	this->worth = worth;
}

Property::Property(unsigned int worth) {
	this->worth = worth;
}

void Property::tostr() {

}

void Property::fromJson(json json) { }

json Property::toJson() { return 0; }
