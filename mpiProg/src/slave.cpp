#include <slave.hpp>

unsigned long long fastPower(unsigned long long a, unsigned long long n)
{
    unsigned long long result = 1;
    unsigned long long power = n;
    unsigned long long value = a;

    while (power>0)
    {
        if (power & 1) // Sprawdzenie parzystosci (true - nieparzyste)
        {
            result = result*value;
        }
        value = value*value;
        power >>= 1; // Dzielenie przez 2
    }
    return result;
}

void slave()
{

}