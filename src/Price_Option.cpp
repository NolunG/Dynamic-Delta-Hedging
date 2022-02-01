#include "Price_Option.h"
#include "Stock.h"
#include "Option.h"
#include "math.h"
#include "time.h"
#include "normalCDF.h"
#include <iostream>

Price_Option::Price_Option()
{
    //ctor
}

Price_Option::~Price_Option()
{
    //dtor
}

double Price_Option::Black_Scholes_Option_Price(Option& option, Stock& stock, double time_to_maturity) {
    double spot = stock.Getspot();
    double time = time_to_maturity;
    double sigma = option.Getsigma();
    double rate = stock.Getrate();
    double strike = option.Getstrike_price();
    double price;
    normalCDF phi{};

    double d1 = (1 / (sigma * sqrt(time))) * (log(spot / strike) + (rate + sigma * sigma / 2) * time);
    double d2 = d1 - sigma * sqrt(time);

    if (option.GetisCall()) {
        price = phi.cdfFromZ(d1) * spot - phi.cdfFromZ(d2) * strike * exp(-rate * time);
    }
    else {
        price =  phi.cdfFromZ(-d2) * strike * exp(-rate * time) - phi.cdfFromZ(-d1) * spot;
    }
    return price;
}

double Price_Option::Black_Scholes_Option_Delta(Option& option, Stock& stock, double time_to_maturity) {
    double spot = stock.Getspot();
    double time = time_to_maturity;
    double sigma = option.Getsigma();
    double rate = stock.Getrate();
    double strike = option.Getstrike_price();
    double price;
    normalCDF phi{};
    double d1 = (1 / (sigma * sqrt(time))) * (log(spot / strike) + (rate + sigma * sigma / 2) * time);
    double d2 = d1 - sigma * sqrt(time);

    if (option.GetisCall())
        return phi.cdfFromZ(d1);
    else
        return phi.cdfFromZ(d1)-1;
}

// Temporary functions, just to get around with volatility as of now
double Price_Option::Black_Scholes_Option_Price(double spot, double time, double sigma, double rate, double strike, bool isCall) {
    //std::cout << spot << " " << time << " " << sigma << " " << rate << " " << strike << " " << std::endl;
    double price;
    normalCDF phi{};

    double d1 = (1 / (sigma * sqrt(time))) * (log(spot / strike) + (rate + sigma * sigma / 2) * time);
    double d2 = d1 - sigma * sqrt(time);

    if (isCall) {
        price = phi.cdfFromZ(d1) * spot - phi.cdfFromZ(d2) * strike * exp(-rate * time);
    }
    else {
        price = phi.cdfFromZ(-d2) * strike * exp(-rate * time) - phi.cdfFromZ(-d1) * spot;
    }
    return price;
}

double Price_Option::Black_Scholes_Option_Delta(double spot, double time, double sigma, double rate, double strike, bool isCall) {

    double price;
    normalCDF phi{};

    double d1 = (1 / (sigma * sqrt(time))) * (log(spot / strike) + (rate + sigma * sigma / 2) * time);
    double d2 = d1 - sigma * sqrt(time);

    if (isCall) {
        return phi.cdfFromZ(d1);
    }
    else {
        return phi.cdfFromZ(d1)-1;
    }
}
