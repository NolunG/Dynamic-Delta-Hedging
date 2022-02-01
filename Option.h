#ifndef OPTION_H
#define OPTION_H


class Option
{
    public:
        Option();
        Option( double strike_price, double sigma, bool);
        virtual ~Option();

        double Getstrike_price() { return strike_price; }
        void Setstrike_price(double val) { strike_price = val; }
        double Getsigma() { return sigma; }
        void Setsigma(double val) { sigma = val; }
        bool GetisCall() { return isCall; }
        void SetisCall(bool val) { isCall = val; }

    protected:

    private:
        void init();
        double strike_price;
        bool isCall;
        double sigma;
};

#endif // OPTION_H
