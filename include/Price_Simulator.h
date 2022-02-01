#ifndef PRICE_SIMULATOR_H
#define PRICE_SIMULATOR_H
#include "Stock.h"
#include "Option.h"

using namespace std;

class Price_Simulator
{
    public:
        Price_Simulator();
        virtual ~Price_Simulator();
        double simulate_and_save_results(Stock &stock, Option& option, int period, int total_paths, double time_to_maturity);
    protected:

    private:
};

#endif // PRICE_SIMULATOR_H
