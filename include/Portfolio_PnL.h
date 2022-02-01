#ifndef PORTFOLIO_PNL_H
#define PORTFOLIO_PNL_H
#include <map>
#include "vector"

using namespace std;

class Portfolio_PnL
{
    public:
        Portfolio_PnL();
        virtual ~Portfolio_PnL();
        void calculate_blm_pnl_and_save(vector<double> interest_rates, vector<double> stock_prices, vector<double> option_prices, vector<double> time_to_maturity, double strike, bool isCall, map<string, double> rates_map);
        double calculate_implied_volatility(double target,  double strike, double spot, double interest_rate, double time_to_maturity, bool isCall);

    protected:

    private:
};

#endif // PORTFOLIO_PNL_H
