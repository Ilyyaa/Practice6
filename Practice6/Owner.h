#pragma once
#include <string>
#include <vector>
#include "Property.h"
#include <iostream>
#include "Ijsonio.h"
#include "PropertyFactoryMethod.h"
using namespace std;
class Owner : public Ijsonio
{
private:
	std::string fullname;
	std::string inn;
	std::vector<Property*> properties;
public:
	void addProperty(Property* property);
	void deleteProperty(unsigned int index);
	double Tax(vector<Property*>); //метод вычисления общей суммы налога на имущество для собственника
	Owner(std::string fullname = "", std::string inn = "");
	string getFullname();
	string getInn();
	void tostr();
	int getSizeProperties();
	vector<Owner> addOwner(vector<Owner>& owners);
	vector<Owner> deleteOwner(vector<Owner>& owners, int number);
	void fromJson(nlohmann::json json) override;
	nlohmann::json toJson() override;
};

