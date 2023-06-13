#include "Owner.h"
#include <string>
#include <vector>
#include <conio.h>
#include "Property.h"
#include "Appartment.h"
#include "Car.h"
#include "CountryHouse.h"
#include "json.hpp"
using namespace nlohmann;
using namespace std;

void Owner::addProperty(Property* property) {
	properties.push_back(property);
}

void Owner::tostr() {
	for (int i = 0; i < properties.size(); i++) {
		properties[i]->tostr();
	}
}

vector<Owner> Owner::addOwner(vector<Owner>& owners) {
	string name, inn, pom;
	cout << "Введите имя собственника: "; cin >> pom; name = pom; getline(cin, name);
	cout << "Введите ИНН: "; cin >> inn;
	if (inn.size() != 16) {
		cout << "ИНН введён некорректно. Повторите ввод: "; cin >> inn;
	}
	string full = pom + name;
	Owner P(full, inn);
	cout << endl << "Сколько квартир имеет собственник: "; int k; cin >> k;
	for (int i = 0; i < k; i++) {
		cout << "Введите стоимость квартиры: "; unsigned int worth; cin >> worth; cout << endl;
		cout << "Введите площадь квартиры в кв. км: "; double square; cin >> square; cout << endl;
		P.addProperty(new Appartment(worth, square));
	}
	cout << endl << "Сколько машин имеет собственник: "; cin >> k;
	for (int i = 0; i < k; i++) {
		cout << "Введите стоимость машины: "; unsigned int worth; cin >> worth; cout << endl;
		cout << "Введите количество лошадиных сил: "; double horsepower; cin >> horsepower; cout << endl;
		P.addProperty(new Car(worth, horsepower));
	}
	cout << endl << "Сколько загородных домов имеет собственник: "; cin >> k;
	for (int i = 0; i < k; i++) {
		cout << "Введите стоимость дома: "; unsigned int worth; cin >> worth; cout << endl;
		cout << "Введите удалённость дома от города в км: "; unsigned int distance_from_city; cin >> distance_from_city; cout << endl;
		P.addProperty(new CountryHouse(worth, distance_from_city));
	}
	owners.push_back(P);
	return owners;
}

vector<Owner> Owner::deleteOwner(vector<Owner>& owners, int number) {
	if (number >= 0 && number < owners.size()) {
		owners.erase(owners.begin() + number);
	}
	return owners;
}

void Owner::deleteProperty(unsigned int index) {
	if (index >= 0 && index < properties.size()) {
		properties.erase(properties.begin() + index);
	}
}

double Owner::Tax(vector<Property*> prop) {
	double sum = 0;
	for (size_t i = 0; i < prop.size(); i++) {
		sum += prop[i]->calculateTax();
	}
	return sum;
}

Owner::Owner(std::string fullname, std::string inn) {
	this->fullname = fullname;
	this->inn = inn;
}

string Owner::getFullname() {
	return fullname;
}

string Owner::getInn() {
	return inn;
}

int Owner::getSizeProperties() {
	return properties.size();
}

void Owner::fromJson(nlohmann::json json) {
	nlohmann::json j = json["Owner"].get<nlohmann::json>();
	fullname = j["fullname"].get<string>();
	inn = j["inn"].get<string>();
	vector<nlohmann::json> dop = j["properties"].get<vector<nlohmann::json>>();
	for (nlohmann::json prop : dop) {
		string key = prop.items().begin().key();
		Property* p = PropertyFactoryMethod::getProperty(key, prop);
		properties.push_back(p);
	}
}

nlohmann::json Owner::toJson() {
	json owner;
	owner["fullname"] = fullname;
	owner["inn"] = inn;
	owner["sumtax"] = Tax(properties);
	vector<json> propert;
	for (Property* p : properties) {
		propert.push_back(p->toJson());
	}
	owner["taxs"] = propert;
	return owner;
}