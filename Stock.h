#ifndef STOCK_H
#define STOCK_H


class Stock
{
    public:
        Stock();
        virtual ~Stock();
        Stock(double spot, double drift, double dividend, double rate);

        double Getspot() { return spot; }
        void Setspot(double val) { spot = val; }
        double Getdrift() { return drift; }
        void Setdrift(double val) { drift = val; }
        double Getrate() { return rate; }
        void Setrate(double val) { rate = val; }
        double Getdividend() { return dividend; }
        void Setdividend(double val) { dividend = val; }

    protected:

    private:
        double spot;
        double rate;
        double drift;
        double dividend;
};

#endif // STOCK_H
