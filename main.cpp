#include <iostream>
#include <fstream>
#include <ctime>
#include <map>
#include "Option.h"
#include "Stock.h"
#include "Price_Simulator.h"
#include <string>
#include "vector"
#include "Price_Option.h"
#include <bits/stdc++.h>
#include "Portfolio_PnL.h"
#include "Unit_Test.h"


using namespace std;

map<string, double> readRateOrStockPrice(string startDate, string endDate, string path);
map<string, double> readOptionPrices(string startDate, string endDate, string expiry, string option_flag, string strike);
/* Function to convert integer form of year, month and day into struct tm fromm std library to store in a date form
*/
std::tm make_tm(int year, int month, int day);
/* Function that returns difference between two dates in terms of years, as asked in the exercice. So 365 days of difference is equal to 1 .
*/
double getDiffTwoDates(string date1, string date2);

vector<double> getVectorFromMap(map<string, double> anyMap) {
    vector<double> returnMap;
    map<string, double>::iterator itr;
    for (itr = anyMap.begin(); itr != anyMap.end(); ++itr) {
        returnMap.push_back(itr->second);
    }
    return returnMap;
}

vector<double> getDailyTimeToMaturities(map<string, double> anyMap, string expiry) {
    vector<double> tmts;
    map<string, double>::iterator itr;
    for (itr = anyMap.begin(); itr != anyMap.end(); ++itr) {
        double tmt = getDiffTwoDates(itr->first, expiry);
        cout << tmt << endl;
        tmts.push_back(tmt*1.03);  // Here will come the getBusinessDay difference function
    }
    return tmts;
}

int main()
{

    Unit_Test ut;
    cout << "Running all Unit tests first to very the functionality" << endl;
    ut.runAllUnitTests();
    cout << "All unit tests completed" << endl;
    // Define the parameters for the simulation: Undelying Stock, Option details, period, time to maturity and number of sample paths to generate
    Stock stock{100,0.05, 0.0, 0.025};
    Option option{105,0.24,true};
    int period = 100;
    int number_of_paths = 100;
    double time_to_maturity = 0.4;

    std::cout << "Running Part 1 of the Assignment: Simulated Prices and Portfolio PnL" << std::endl;
    // Run the simulation and store outputs
    Price_Simulator ps{};
    ps.simulate_and_save_results(stock, option, period, number_of_paths, time_to_maturity);


    std::cout << "Part 1 of Completed: Check the results in Results.csv" << std::endl;
    std::cout << "Part 2 of the assignment: BS Model on Real data and PnL" << std::endl;

    std::cout << getDiffTwoDates("2011-01-04", "2011-01-06") << std::endl;
    bool isAllDataCorrect = false;
    std::string window_start;
    std::string window_end;
    std::string expiry_option;
    std::string strike_price;
    string isCallS;
    bool isCall = true;

    cout << "Enter the dates in following format yyyy-mm-dd format without space" << endl;


    cout << "Enter window start date:" << endl;
    cin >> window_start;
    cout << "Enter window end date:" << endl;
    cin >> window_end;
    cout << "Enter expiry date of option" << endl;
    cin >> expiry_option;
    cout << "Enter Strike Price " << endl;
    cin >> strike_price;
//    cout << "Enter Call, Put" << endl;
//    cin >> isCallS;
//    if (isCallS )
//    do {
//        cout << "Enter the dates in following format yyyy-mm-dd format without space:" << endl;
//        cout << "Enter the start date:" << endl;
//                std::cin >> startdate;
//                std::cout << "Enter the end date:" << endl;
//                std::cin >> enddate;
//                std::cout << "Enter the maturity:" << endl;
//                std::cin >> maturity;
//    } while(!isAllDataCorrect);

    map<string, double> interest_rates = readRateOrStockPrice(window_start, window_end, "./data/interest.csv");
    map<string, double> stock_prices = readRateOrStockPrice(window_start, window_end, "./data/sec_GOOG.csv");
    map<string, double> option_prices = readOptionPrices(window_start,window_end,expiry_option,"C",strike_price);

    if(interest_rates.size() != stock_prices.size() || option_prices.size() != stock_prices.size())
        {std::cout << "Something is going wrong, please check your input, maybe your input does not have all option values" << std::endl;
        std::cout << interest_rates.size() << " " << stock_prices.size() << " " << option_prices.size() << std::endl;}

    Portfolio_PnL pnl_book{};
    pnl_book.calculate_blm_pnl_and_save(getVectorFromMap(interest_rates), getVectorFromMap(stock_prices), getVectorFromMap(option_prices), getDailyTimeToMaturities(interest_rates,expiry_option),
                                        stod(strike_price), isCall, interest_rates);

    return 0;
}
// Interest rate and sotck price have structure so the function can be used interchangeably for both
map<string, double> readRateOrStockPrice(std::string startDate, std::string endDate, std::string path) {
    //Assuming yyyy-mm-dd
    map<string,double> rate_map;
    ifstream infile(path);
    int read_flag = 0;
    string line;
    getline( infile, line );
    while (getline( infile, line )){

        stringstream current_line(line);
        string token;
        getline(current_line, token, ',');
        string cur_date = token;
        if (getDiffTwoDates(startDate, cur_date) < 0) {
            continue;
        }

        if (getDiffTwoDates(endDate, cur_date) > 0) {
            break;
        }

        getline(current_line, token, ',');
        rate_map.insert(make_pair(cur_date, stod(token)));
    }
    infile.close();
    return rate_map;
}


map<string, double> readOptionPrices(string startDate, string endDate, string expiry, string option_flag, string strike) {
    map<string,double> option_map;
    ifstream infile("./data/op_GOOG.csv");
    int read_flag = 0;
    string line;
    getline( infile, line );
    while (getline( infile, line )){

        stringstream current_line(line);
        string token;
        getline(current_line, token, ',');
        string cur_date = token;
        if (getDiffTwoDates(startDate, cur_date) < 0) {
            continue;
        }

        if (getDiffTwoDates(endDate, cur_date) > 0) {
            break;
        }

        getline(current_line, token, ',');
        string ex_date = token;
        getline(current_line, token, ',');
        string op_flag = token;
        getline(current_line, token, ',');
        //cout << cur_date << " " << ex_date << " " << op_flag << " " << token << endl;
        if (getDiffTwoDates(ex_date, expiry) == 0 && op_flag == option_flag && token == strike) {
            getline(current_line, token, ',');
            double bid = stod(token);
            getline(current_line, token, ',');
            double ask = stod(token);
            option_map.insert(make_pair(cur_date, (bid+ask)/2));

        } else {
            continue;
        }
    }
    infile.close();
    return option_map;
}

std::tm make_tm(int year, int month, int day)
{
    std::tm tm = {0};
    tm.tm_year = year - 1900; // years count from 1900
    tm.tm_mon = month - 1;    // months count from January=0
    tm.tm_mday = day;         // days count from 1
    return tm;
}

double getDiffTwoDates(string date1, string date2) {

    std::tm tm1 = make_tm(stoi(date1.substr(0, 4)),stoi(date1.substr(5, 6)),stoi(date1.substr(8,9)));    // April 2nd, 2012
    std::tm tm2 = make_tm(stoi(date2.substr(0, 4)),stoi(date2.substr(5, 6)),stoi(date2.substr(8,9)));

    std::time_t time1 = std::mktime(&tm1);
    std::time_t time2 = std::mktime(&tm2);

    return std::difftime(time2, time1) / (365*60*60*24);
}
