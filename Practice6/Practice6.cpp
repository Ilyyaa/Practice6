#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <clocale>
#include "Owner.h"
#include "Property.h"

using namespace std;

void create(vector<Owner>& owners);
void print(vector<Owner> owners);
void menu();
json initfile(string fileName);
vector<Owner> vec_owners(json Obj);
vector<json> jsonObjFromOwners(vector<Owner> owners);
void saveFile(string fileName, json jowners);

int main() {
	setlocale(LC_CTYPE, "rus");

	string filename;
	cout << "Введите название файла, где находится список собственников: ";
	cin >> filename;
	//filename = "owners.json";
	json Obj = initfile(filename);
	vector<Owner> owners = vec_owners(Obj);

	//create(owners);
	int size = owners.size() - 1;
	menu();
	cout << endl << "Сделайте свой выбор: "; int choise; cin >> choise;

	while (choise != 0) {
		switch (choise) {
		case 1: print(owners); break;
		case 2:
			if (size == -1) {
				Owner P("", "");
				owners.push_back(P);
				size = 0;
				owners[size].addOwner(owners);
			}
			else {
				owners[size].addOwner(owners);
				size++;
			}
			break;
		case 3:
			int ch;
			if (size + 1 != 0)
			{
				cout << endl << "Какого собственника нужно удалить? Выберите от 1 до " << size + 1 << ": ";  cin >> ch;
				while (ch <= 0 || ch > size + 1) {
					cout << endl << "Таких собственников нет. Измените свой выбор: "; cin >> ch;
				}
				ch -= 1;
				owners[ch].deleteOwner(owners, ch);
				size--;
			}
			else if (size + 1 == 0)
			{
				cout << endl << "Собственников больше нет." << endl;
			}


			break;
		case 4: cout << endl << "Какому собственнику вы хотите добавить собственность? Выберите от 1 до " << size + 1 << ": "; cin >> ch;
			while (ch <= 0 || ch > size + 1) {
				cout << endl << "Таких собственников нет. Измените свой выбор: "; cin >> ch;
			}
			ch -= 1;
			cout << endl << "Какую собственность вы хотите добавить? (1 - квартира, 2 - машина, 3 - дом) Выберите: "; int num; cin >> num;
			while (num < 1 || num>3) {
				cout << "Такой собственности нет. Измените свой выбор:"; cin >> num;
			}
			switch (num) {
			case 1: cout << endl << "Сколько квартир имеет собственник: "; int k; cin >> k;
				for (int i = 0; i < k; i++) {
					cout << "Введите стоимость квартиры: "; unsigned int worth; cin >> worth; cout << endl;
					cout << "Введите площадь квартиры в кв. км: "; double square; cin >> square; cout << endl;
					owners[ch].addProperty(new Appartment(worth, square));
				}
				break;
			case 2: cout << endl << "Сколько машин имеет собственник: "; cin >> k;
				for (int i = 0; i < k; i++) {
					cout << "Введите стоимость машины: "; unsigned int worth; cin >> worth; cout << endl;
					cout << "Введите количество лошадиных сил: "; double horsepower; cin >> horsepower; cout << endl;
					owners[ch].addProperty(new Car(worth, horsepower));
				}
				break;
			case 3: cout << endl << "Сколько загородных домов имеет собственник: "; cin >> k;
				for (int i = 0; i < k; i++) {
					cout << "Введите стоимость дома: "; unsigned int worth; cin >> worth; cout << endl;
					cout << "Введите удалённость дома от города в км: "; unsigned int distance_from_city; cin >> distance_from_city; cout << endl;
					owners[ch].addProperty(new CountryHouse(worth, distance_from_city));
				}
				break;
			default: cout << endl << "Такой функции нет."; break;
			}
			break;
		case 5:

			cout << "У какого собаственника вы хотите удалить собственность?от 1 до" << size + 1 << ":"; cin >> ch;
			while (ch <= 0 || ch > size + 1) {
				cout << endl << "Таких собственников нет. Измените свой выбор: "; cin >> ch;
			}
			ch -= 1;
			if (owners[ch].getSizeProperties() != 0)
			{
				cout << "Какую по счёту собственность нужно удалить? Выберите от 1 до " << owners[ch].getSizeProperties() << ": "; cin >> num;
				while (num <= 0 || num > owners[ch].getSizeProperties()) {
					cout << endl << "Такой собственности нет. Измените свой выбор: "; cin >> num;
				}
			}
			else
			{
				cout << endl << "У собственника нет собственности" << endl;
			}
			num -= 1;
			owners[ch].deleteProperty(num);

			break;
		default: cout << endl << "Такой функции нет."; break;
		}
		cout << endl;
		menu();
		if (size == -1) {
			cout << endl << "Собственников не осталось. Вызовите 2 функцию: "; cin >> choise;
			while (choise != 2 && choise != 0) {
				cout << endl << "Собственников не осталось. Вызовите 2 функцию: "; cin >> choise;
			}
		}
		else {
			cout << endl << "Сделайте свой выбор: "; cin >> choise;
		}
	}

	cout << "Введите название файла в формате 'название.json', в который будет сохранён список собственников: ";
	cin >> filename;
	//filename = "out.json";
	json obj;
	vector<json> ownerObj = jsonObjFromOwners(owners);
	obj["Owners"] = ownerObj;
	saveFile(filename, obj);

}

// делает из вектора Owner-ов вектор json-ов
vector<json> jsonObjFromOwners(vector<Owner> owners) {
	vector<json> ownersJson;
	for (Owner owner : owners) {
		json obj;
		obj["Owner"] = owner.toJson();
		ownersJson.push_back(obj);
	}
	return ownersJson;
}

//запись json в файл
void saveFile(string fileName, json jowners) {
	ofstream fout(fileName);
	fout << jowners;
	fout.close();
}

// создание вектора owner-ов из json данных
vector<Owner> vec_owners(json Obj) {
	vector<nlohmann::json> jOwners = Obj["Owners"].get<vector<nlohmann::json>>();
	vector<Owner> owners;
	for (nlohmann::json jowner : jOwners) {
		Owner o;
		o.fromJson(jowner);
		owners.push_back(o);
	}
	return owners;
}


// получение из json файла данных
json initfile(string fileName) {
	ifstream fin(fileName);
	json jdog = json::parse(fin);
	fin.close();
	return jdog;
}

void print(vector<Owner> owners) {
	int num = 1;
	for (Owner o : owners) {
		cout << num << ". ";
		cout << "Имя собственника: " << o.getFullname() << endl << "ИНН: " << o.getInn() << endl << endl << "Собственность: " << endl;
		o.tostr();
		cout << endl;
		num++;
	}
}

void menu() {
	cout << "0. Выход и сохранение файла." << endl;
	cout << "1. Вывести список собственников на экран." << endl;
	cout << "2. Добавить собственника в список." << endl;
	cout << "3. Удалить собственника из списка." << endl;
	cout << "4. Добавить собственность собственнику." << endl;
	cout << "5. Удалить собственность собственника." << endl;
}