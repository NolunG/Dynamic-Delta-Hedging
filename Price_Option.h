#ifndef PRICE_OPTION_H
#define PRICE_OPTION_H
#include "Stock.h"
#include "Option.h"

class Price_Option
{
    public:
        Price_Option();
        virtual ~Price_Option();
        double Black_Scholes_Option_Price(Option& option, Stock& stock, double time_to_maturity);
        double Black_Scholes_Option_Delta(Option& option, Stock& stock, double time_to_maturity);
        double Black_Scholes_Option_Price(double spot, double time, double sigma, double rate, double strike, bool isCall);
        double Black_Scholes_Option_Delta(double spot, double time, double sigma, double rate, double strike, bool isCall);
    protected:

    private:

};

#endif // PRICE_OPTION_H
