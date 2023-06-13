#include "PropertyFactoryMethod.h"

Property* PropertyFactoryMethod::getProperty(std::string key, json prop) {
	if (key == "Appartment") {
		Appartment ap(0, 0);
		ap.fromJson(prop);
		return new Appartment(ap);
	}
	if (key == "Car") {
		Car c(0, 0);
		c.fromJson(prop);
		return new Car(c);
	}
	else {
		CountryHouse ch(0, 0);
		ch.fromJson(prop);
		return new CountryHouse(ch);
	}
}
