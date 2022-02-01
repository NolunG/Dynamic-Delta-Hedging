#ifndef NORMALCDF_HPP
#define NORMALCDF_HPP


class normalCDF
{
    public:
        normalCDF();
        virtual ~normalCDF();
        double cdfFromZ(double x);
    protected:

    private:
        const double A1 = 0.319381530;
        const double A2 = -0.35653782;
        const double A3 = 1.781477937;
        const double A4 = -1.821255978;
        const double A5 = 1.330274429;
        const double B = 0.2316419;
        const double NORMALIZER = 0.39894228;
};

#endif // NORMALCDF_HPP
