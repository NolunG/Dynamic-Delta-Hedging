#include "Unit_Test.h"
#include <iostream>
#include <fstream>
#include "Option.h"
#include "Stock.h"
#include "Price_Simulator.h"
#include <string>
#include "Price_Option.h"
#include "Portfolio_PnL.h"

Unit_Test::Unit_Test()
{
    //ctor
}

Unit_Test::~Unit_Test()
{
    //dtor
}

void runBlack_Scholes_Price_Test() {

    Price_Option op;
    // We will verify if the Black Scholes Price calculation is working correctly. I have taken this values from an online calculator, to verify the correctness
    double underlying_price = 630;
    double strike_price = 600;
    double bank_rate = 0.002;
    double day_till_maturity = 0.0822;
    double sigma = 0.3;

    double black_scholes_real_ans = 39.45;  // taken from online calculcator

    double our_ans = op.Black_Scholes_Option_Price(underlying_price, day_till_maturity, sigma, bank_rate, strike_price, true);

    if (abs(our_ans - black_scholes_real_ans) < 0.2) {
        cout << "Black Scholes Option Price function returns correct value" << endl;
    } else {
        cout << "Black Scholes Option Price function does not return correct value" << " " << our_ans << endl;
    }

}

void runBlack_Scholes_Delta_Test() {

    Price_Option op;
    // We will verify if the Black Scholes Delta calculation is working correctly. I have taken this values from an online calculator, to verify the correctness
    double underlying_price = 630;
    double strike_price = 600;
    double bank_rate = 0.002;
    double day_till_maturity = 0.0822;
    double sigma = 0.3;

    double black_scholes_real_ans = 0.729;  // taken from online calculcator

    double our_ans = op.Black_Scholes_Option_Delta(underlying_price, day_till_maturity, sigma, bank_rate, strike_price, true);

    if (abs(our_ans - black_scholes_real_ans) < 0.05) {
        cout << "Black Scholes Option Delta function returns correct value" << endl;
    } else {
        cout << "Black Scholes Option Delta function does not return correct value" << " " << our_ans << endl;
    }

//    if (abs(our_ans - black_scholes_real_ans) < 0.05) {
//        cout << "Black Scholes Option Delta function returns correct value" << endl;
//    } else {
//        cout << "Black Scholes Option Delta function does not return correct value" << " " << our_ans << endl;
//    }
}

void runImplied_Volatility_Tets() {
    Portfolio_PnL pl;
    // We will verify if the implied volatility calculation is working correctly. I have taken this values from an online calculator, to verify the correctness
    double option_target_price = 40;
    double underlying_price = 630;
    double strike_price = 600;
    double bank_rate = 0.002;
    double day_till_maturity = 0.0822;

    double vol_real_ans = 0.3089;  // taken from online calculcator
    double our_ans = pl.calculate_implied_volatility(option_target_price, strike_price, underlying_price, bank_rate, day_till_maturity, true);

    if (abs(our_ans - vol_real_ans) < 0.05) {
        cout << "Implied Volatility function returns correct value" << endl;
    } else {
        cout << "Implied VOlatility function does not return correct value" << endl;
    }

}
void Unit_Test::runAllUnitTests()
{
    runBlack_Scholes_Price_Test();
    runBlack_Scholes_Delta_Test();
    runImplied_Volatility_Tets();

}

