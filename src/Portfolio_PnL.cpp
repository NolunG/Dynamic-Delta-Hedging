#include "Portfolio_PnL.h"
#include <map>
#include <ctime>
#include "Price_Option.h"
#include "vector"
#include "math.h"
#include <fstream>
#include <iostream>

Portfolio_PnL::Portfolio_PnL()
{
}

Portfolio_PnL::~Portfolio_PnL()
{
}

double Portfolio_PnL::calculate_implied_volatility(double target,  double strike, double spot, double interest_rate, double time_to_maturity, bool isCall) {
    double epsilon = 0.0001;
    double a = 0.00001, b = 1.0;

    Price_Option op{};
    double x = 0.5 * (a + b);
    double BSMprice = op.Black_Scholes_Option_Price(spot, time_to_maturity, x, interest_rate, strike, isCall);
    //cout << "Target: " << target << " " << spot << " " << time_to_maturity << " " << interest_rate << endl;
    int n=0;
    double y = BSMprice;
    while (abs(y-target) > epsilon){
        //cout << y << " " << x << " " << a << " " << b << endl;
        n++;
        if(n>1000000){
            return x;
        }
        if (y < target) {
            a = x;
        }
        if (y > target) {
            b = x;
        }

        x = 0.5 * (a + b);
        y = op.Black_Scholes_Option_Price(spot, time_to_maturity, x, interest_rate, strike, isCall);
    }

        return x;
}

void Portfolio_PnL::calculate_blm_pnl_and_save(vector<double> interest_rates, vector<double> stock_prices , vector<double> option_prices, vector<double> time_to_maturity,
                                        double strike, bool isCall, map<string, double> rates_map)
{
    vector<double> implied_volatility;
    vector<double> delta;
    vector<double> hedging_error;
    vector<double> pnl;
    vector<double> pnl_with_hedge;
    vector<double> portfolio;

    double dT = 1/252.0;

    hedging_error.push_back(0);
    pnl_with_hedge.push_back(0);

    Price_Option op{};

    // Total Wealth is PNL with hedging error itself, hence it is not calculcated

    for (int i = 0; i < interest_rates.size(); ++i) {

        //I should have taken interest rate as 1/100 directly, but I used common function for both interest rate and stocks, I have to divide here
        interest_rates[i] = interest_rates[i]/100;
        implied_volatility.push_back(calculate_implied_volatility(option_prices[i], strike, stock_prices[i], interest_rates[i], time_to_maturity[i], isCall));

        double bsm_delta = op.Black_Scholes_Option_Delta(stock_prices[i], time_to_maturity[i], implied_volatility[i], interest_rates[i], strike, isCall);
        delta.push_back(bsm_delta);
        pnl.push_back(option_prices[0] - option_prices[i]);
        double portfolioVal;

        if(i < 1)
            portfolioVal = option_prices[i] - delta[i]*stock_prices[i];
        else {
            portfolioVal = delta[i-1]*stock_prices[i] + portfolio[i-1]*exp(interest_rates[i]*dT) - delta[i]*stock_prices[i];
            double hedge_error = delta[i-1]*stock_prices[i] + portfolio[i-1]*exp(interest_rates[i-1]*dT) - option_prices[i];
            hedging_error.push_back(hedge_error);
            pnl_with_hedge.push_back(hedge_error);

        }
        portfolio.push_back(portfolioVal);
    }

    std::ofstream output;
    output.open("Task_2_Result_Table.csv", std::ios_base::app);

    map<string, double>::iterator itr;
    output << "Date,Stock Price, Option Price, Implied Volatility, Delta, Hedging Error, PNL, PNL with hedge, Total Wealth" << endl;
    int i = 0;
    for (itr = rates_map.begin(); itr != rates_map.end(); ++itr, i++) {
        output << itr->first << "," << stock_prices[i] << "," << option_prices[i] << "," << implied_volatility[i] << "," << delta[i] << "," << hedging_error[i] << "," << pnl[i]<< "," << pnl_with_hedge[i] << "," << pnl_with_hedge[i] << endl;
    }
}


