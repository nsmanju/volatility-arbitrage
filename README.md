# volatility-arbitrage
Creating a Volatility Arbitrage Strategy with C++ code
Taken from _https://medium.com/@devillar/volatility-arbitrage-strategy-with-a-c-example-0ace5c87ab1d_
This is a Simple Volatility Arbitrage Code Example in C++ that estimates implied and realized volatility, 
calculates option prices using the Black-Scholes model, and then decides on a trade based on volatility differences.


_The origial code (see vola_arbitrage.cpp) had some accuracy issues w.r.t. the Black-Scholes formula. I have refatored this code
 under vola_arbitrage_improved.cpp using my own skills and VS Code Co-Pilot_

### Here is a detailed explanation:
```
This function is intended to implement the Black-Scholes formula, which is a mathematical model used to calculate
the theoretical price of European-style options.
The function takes six parameters: the current price of the underlying asset (S), the strike price of the option (K),
the time to expiration in years (T), the risk-free interest rate (r), the volatility of the underlying asset (sigma),
and a boolean flag (isCall) indicating whether the option is a call (true) or a put (false).

Inside the function, two intermediate variables, d1 and d2, are calculated. These are standard components of
the Black-Scholes formula and are used to determine the probabilities that the option will finish in the money,
adjusted for the time value  of money and volatility. The formulas for d1 and d2 involve logarithms, the risk-free
rate, volatility, and the time to expiration.

The function then checks the isCall flag. If it is true, it attempts to calculate the price of a call option;
otherwise,it calculates the price of a put option. However, the implementation uses exp(-0.5 * d1 * d1) and
exp(-0.5 * d2 * d2),which are not correct for the Black-Scholes formula. The standard formula uses the cumulative
distribution function (CDF) of the standard normal distribution, not the exponential of the negative half-square.
This means the function will not return correct option prices as written.


Output:
Realized Volatility: 0.017066
Option Price (Call): 17.7773
Sell Volatility (Implied > Realized)
```
