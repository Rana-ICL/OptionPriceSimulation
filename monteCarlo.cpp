#include <iostream>
#include <cmath>
#include <random>
#include <fstream>
#include <gnuplot-iostream.h>

using namespace std;

// function to calculate the option price using Black-Scholes formula
double blackScholes(double S, double K, double r, double sigma, double T)
{
    double d1 = (log(S / K) + (r + sigma * sigma / 2) * T) / (sigma * sqrt(T));
    double d2 = d1 - sigma * sqrt(T);
    double Nd1 = 0.5 * (1 + erf(d1 / sqrt(2)));
    double Nd2 = 0.5 * (1 + erf(d2 / sqrt(2)));
    double callPrice = S * Nd1 - K * exp(-r * T) * Nd2;
    return callPrice;
}

int main()
{
    // parameters
    double S = 100;     // stock price
    double K = 110;     // strike price
    double r = 0.05;    // risk-free rate
    double sigma = 0.2; // volatility
    double T = 1;       // time to maturity
    int N = 100000;     // number of simulations

    // set up random number generator
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> dist(0, 1);

    // simulate N paths and calculate the option price for each path
    vector<double> optionPrices(N);
    for (int i = 0; i < N; i++)
    {
        double St = S * exp((r - sigma * sigma / 2) * T + sigma * sqrt(T) * dist(gen));
        double payoff = max(St - K, 0.0);
        double discountedPayoff = payoff * exp(-r * T);
        optionPrices[i] = discountedPayoff;
    }
    double optionPrice = accumulate(optionPrices.begin(), optionPrices.end(), 0.0) / N;

    // calculate the option price using Black-Scholes formula
    double bsPrice = blackScholes(S, K, r, sigma, T);

    // plot the results using gnuplot and save as PNG
    Gnuplot gp;
    gp << "set terminal pngcairo enhanced font 'Verdana,12'\n";
    gp << "set output 'Monte_Carlo.png'\n";
    gp << "set xlabel 'Simulations'\n";
    gp << "set ylabel 'Option Price'\n";
    gp << "plot '-' with lines title 'Monte Carlo Option Price', " << bsPrice << " with lines title 'Black-Scholes Option Price'\n";
    for (int i = 0; i < N; i++)
    {
        gp << i << " " << accumulate(optionPrices.begin(), optionPrices.begin() + i + 1, 0.0) / (i + 1) << "\n";
    }
    gp << "e\n";

    // output the results
    cout << "Monte Carlo option price: " << optionPrice << endl;
    cout << "Black-Scholes option price: " << bsPrice << endl;

    return 0;
}
