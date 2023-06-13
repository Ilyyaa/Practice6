#pragma once
#include "Ijsonio.h"
#include "json.hpp"
using namespace nlohmann;
using namespace std;
namespace TAX_RATES
{
	const double CAR_TAX = 0.0007;
	const double CAR_TRUCK_TAX = 0.007;
	const double CAR_LUXURY_TAX = 0.027;
	const double APPARTMENT_TAX = 0.001;
	const double APPARTMENT_LUXURY_TAX = 0.004;
	const double COUNTRY_HOUSE_TAX = 0.01;

	const double LOW_HORSEPOWER = 100;
	const double HIGH_HORSEPOWER = 200;
	const unsigned int LIMIT_DISTANCE_FROM_CITY = 30;
	const int LIMIT_APPARTMENT_SQUARE = 100;
}
using namespace std;

class Property : public Ijsonio // имущество
{
private:
	unsigned int worth; //стоимость
public:
	Property(unsigned int worth = 0);
	virtual double calculateTax();
	double IncomeTax();
	unsigned int getWorth();
	void setWorth(unsigned int worth);
	virtual void tostr();
	~Property();
	void fromJson(json json) override;
	json toJson() override;
};

