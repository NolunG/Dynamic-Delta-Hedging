#include "Option.h"

Option::Option()
{
    init();
}

Option::Option(double strike_price, double sigma, bool isCall)
{
    this->strike_price = strike_price;
    this->sigma = sigma;
    this->isCall = isCall;
}

Option::~Option()
{
    //dtor
}

void Option::init() {
    strike_price = 100;
    sigma = 0.05;
}
