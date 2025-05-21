/* From https://medium.com/@devillar/volatility-arbitrage-strategy-with-a-c-example-0ace5c87ab1d
A Simple Volatility Arbitrage Code Example in C++
demonstrates a basic volatility arbitrage strategy in C++, 
this simplified example estimates implied and realized volatility, 
calculates option prices using the Black-Scholes model, and then decides on a trade based on volatility differences.

Step 1: Calculate Implied and Realized Volatility
To start, we need to calculate the implied volatility from an option price and 
compare it to the realized volatility over a historical period. This will 
inform our arbitrage decisions. */

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::log;
using std::sqrt;
using std::exp;

// Black-Scholes Formula for Option Pricing

// Standard normal cumulative distribution function
double norm_cdf(double x) {
  return 0.5 * (1.0 + std::erf(x / sqrt(2.0)));
}

// Black-Scholes Formula for Option Pricing (corrected)
double blackScholes(double S, double K, double T, double r, double sigma, bool isCall) {
  double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
  double d2 = d1 - sigma * sqrt(T);

  if (isCall) {
    return S * norm_cdf(d1) - K * exp(-r * T) * norm_cdf(d2);
  } else {
    return K * exp(-r * T) * norm_cdf(-d2) - S * norm_cdf(-d1);
  }
}




// Calculate Realized Volatility from Price Datausing PriceList = const std::vector<double>&;

using PriceList = const std::vector<double>&;
//PriceList prices;

double realizedVolatility(PriceList prices) {
    double sum = 0.0;
    int n = prices.size();
    
    for (int i = 1; i < n; ++i) {
        double logReturn = log(prices[i] / prices[i - 1]);
        sum += logReturn * logReturn;
    }
    
    return sqrt(sum / (n - 1));
}

int main() {
    // Example Data: Stock Prices Over Time
    // Apple stock prices for the last ten days from Yahoo Finance
    vector<double> stockPrices = {211, 213, 212, 211, 211, 209, 201};

    // Parameters
    double S = 213; // Spot Price
    double K = 200; // Strike Price 200
    double T = 1.0; // Time to Maturity in Years
    double r = 0.01; // Risk-Free Rate
    double sigmaImplied = 0.1; // 0.1 Implied Volatility, triggers buy.
    //double sigmaImplied = 0.1; // 0.5 Implied Volatility, triggers sell.
    // Calculate Realized Volatility
    double rv = realizedVolatility(stockPrices);
    
    // Calculate Option Price using Black-Scholes
    double optionPrice = blackScholes(S, K, T, r, sigmaImplied, true);
    //double optionPrice = blackScholes(S, K, T, r, sigmaImplied, false);
    // Output the results
    cout << "Realized Volatility: " << rv << endl;
    cout << "Option Price (Call): " << optionPrice << endl;
    //A Simple Volatility Arbitrage Code Example in C++
    // Simple Arbitrage Decision
    if (sigmaImplied > rv) {
        cout << "Sell Volatility (Implied > Realized)" << endl;
    } else {
        cout << "Buy Volatility (Realized > Implied)" << endl;
    }
    
    return 0;
}

 
    
    