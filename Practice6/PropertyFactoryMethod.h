#pragma once
#include "Property.h"
#include "Appartment.h"
#include "Car.h"
#include "CountryHouse.h"

class PropertyFactoryMethod
{
public:
	static Property* getProperty(std::string key, json prop);
};

