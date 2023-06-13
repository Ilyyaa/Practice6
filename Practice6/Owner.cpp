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
	cout << "������� ��� ������������: "; cin >> pom; name = pom; getline(cin, name);
	cout << "������� ���: "; cin >> inn;
	if (inn.size() != 16) {
		cout << "��� ����� �����������. ��������� ����: "; cin >> inn;
	}
	string full = pom + name;
	Owner P(full, inn);
	cout << endl << "������� ������� ����� �����������: "; int k; cin >> k;
	for (int i = 0; i < k; i++) {
		cout << "������� ��������� ��������: "; unsigned int worth; cin >> worth; cout << endl;
		cout << "������� ������� �������� � ��. ��: "; double square; cin >> square; cout << endl;
		P.addProperty(new Appartment(worth, square));
	}
	cout << endl << "������� ����� ����� �����������: "; cin >> k;
	for (int i = 0; i < k; i++) {
		cout << "������� ��������� ������: "; unsigned int worth; cin >> worth; cout << endl;
		cout << "������� ���������� ��������� ���: "; double horsepower; cin >> horsepower; cout << endl;
		P.addProperty(new Car(worth, horsepower));
	}
	cout << endl << "������� ���������� ����� ����� �����������: "; cin >> k;
	for (int i = 0; i < k; i++) {
		cout << "������� ��������� ����: "; unsigned int worth; cin >> worth; cout << endl;
		cout << "������� ���������� ���� �� ������ � ��: "; unsigned int distance_from_city; cin >> distance_from_city; cout << endl;
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