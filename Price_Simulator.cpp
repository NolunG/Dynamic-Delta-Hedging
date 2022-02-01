#include "Price_Simulator.h"
#include "Stock.h"
#include "Option.h"
#include "Price_Option.h"
#include <random>
#include <fstream>
#include <iostream>

using namespace std;

Price_Simulator::Price_Simulator()
{
    //ctor
}

Price_Simulator::~Price_Simulator()
{
    //dtor
}


double Price_Simulator::simulate_and_save_results(Stock &stock, Option& option, int period, int total_paths, double time_to_maturity) {
    std::default_random_engine generator;
    std::normal_distribution<double> normal(0.0,1.0);

    Price_Option op{};

	double dT = time_to_maturity/period;
    double simulated_price[period+1], call_price[period+1], delta[period+1], hedging_error[period+1], portfolio[period+1];
    simulated_price[0] = stock.Getspot();

    call_price[0] = op.Black_Scholes_Option_Price(option, stock, time_to_maturity);
    delta[0] = op.Black_Scholes_Option_Delta(option, stock, time_to_maturity);

    portfolio[0] = call_price[0] - delta[0]*simulated_price[0];  // verify this assumption - this is not accurate, only an approximation
    //hedging_error[0] = call_price[0] - delta[0]*simulated_price[0];

//    portfolio[0] = 0;
//    hedging_error[0] = 0;
    std::ofstream myFile;
    myFile.open("Task_1_hedging_error_new.csv", std::ios_base::app);
    std::ofstream sample_path_file;
    sample_path_file.open("Task_1_stock_path_new.csv", std::ios_base::app);
    std::ofstream option_file;
    option_file.open("Task_1_calculated_option_prices.csv", std::ios_base::app);

    myFile << to_string(hedging_error[0]) << endl;
        while (total_paths--) {
        for(int i = 1; i <= period ;i++) {
            double normalVar = normal(generator);
            simulated_price[i] = simulated_price[i-1]*(1.0 + stock.Getdrift()*dT + option.Getsigma()*sqrt(dT)*normalVar);

            // Because the price of the stock is changed now, I use this {today's) price to calculate the option price
            stock.Setspot(simulated_price[i]);

            call_price[i] = op.Black_Scholes_Option_Price(option, stock, time_to_maturity - (i+1)*dT);
            delta[i] = op.Black_Scholes_Option_Delta(option, stock, time_to_maturity - (i+1)*dT);

            portfolio[i] = delta[i-1]*simulated_price[i] + portfolio[i-1]*exp(stock.Getrate()*dT) - delta[i]*simulated_price[i];
            hedging_error[i] = delta[i-1]*simulated_price[i] + portfolio[i-1]*exp(stock.Getrate()*dT) - call_price[i];

            sample_path_file << simulated_price[i] << ",";
            option_file << call_price[i-1] << ",";
        }
        sample_path_file << endl;
        option_file << endl;
        myFile << to_string(hedging_error[period-1]) << endl;
    }
}
