
#Monte Carlo Option Pricing

This code uses the Monte Carlo method to simulate possible stock price paths and calculate the option price for each path. The results are compared to the theoretical price calculated using the Black-Scholes formula, and a plot of the results is generated using gnuplot.

Getting Started

To run the code, you will need to install the following libraries:

gnuplot-iostream (https://github.com/dstahlke/gnuplot-iostream)
Boost C++ Libraries (https://www.boost.org/)
You can install gnuplot-iostream by cloning the repository and building the library. Boost can be installed using a package manager or by downloading and building the library.

Once you have installed the necessary libraries, you can compile and run the code using a C++ compiler. For example, you can use the following command in a terminal:

css
Copy code
g++ -std=c++11 main.cpp -lboost_iostreams -lboost_system -lboost_filesystem
./a.out
This will compile the code and run the simulation.

Parameters

You can modify the following parameters in the code to change the simulation:

S: the current stock price
K: the strike price of the option
r: the risk-free interest rate
sigma: the volatility of the stock price
T: the time to maturity of the option
N: the number of simulations
Output

The code outputs the following results to the console:

Monte Carlo option price
Black-Scholes option price
It also generates a plot of the Monte Carlo option price and the Black-Scholes option price as a function of the number of simulations. The plot is saved as a PNG file named Monte_Carlo.png.

License

This code is released under the MIT License.
