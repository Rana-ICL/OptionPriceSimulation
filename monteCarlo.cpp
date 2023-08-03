
// Cumulative Distribuation Function 
double NCDF(double value) {
   return 0.5 * erfc(-value * M_SQRT1_2);
}



// MC Simulation for a call option
double MC_Sim(int sims, double ST, double KT, double r, double v, double T) {
    mt19937 gen(random_device{});
    boost::random::normal_distribution<> d(0., 1.);

    double S_adjust = ST * exp(T*(r - 0.5 * v * v));
    double S_cur = 0.0;
    double payoff_sum = 0.0;

    for(int i = 0; i < sims; ++i) {
        double gauss_bm = d(gen);
        S_cur = S_adjust * exp(sqrt(v * v * T) * gauss_bm);
        payoff_sum += std::max(S_cur - KT, 0.0);
    }

    return (payoff_sum / static_cast<double>(sims)) * exp(-r *T);
}


// BS Model for a call option
double BS_Model(double ST, double KT, double rf_rate, double vol, double t) {
    double d1 = (log(ST/KT) + (rf_rate + 0.5 * vol * vol) * t) / (vol * sqrt(t));
    double d2 = d1 - vol * sqrt(t);
    
    return ST * NCDF(d1) - KT * exp(-rf_rate * t) * NCDF(d2);
}



int main() {
    // Parameters for BS and MC
    double r_f = 0.05; // risk-free rate
    double vola = 0.2; // volatitiy
    double t = 1.0; // time
    int num_sims = 5000000; // number of simulations
    double s = 300.0; // Stock price
    double st_p = 10.0; // strike price
    

    // Calculate prices
    double MC_call = MC_Sim(num_sims, s, st_p, r_f, vola, t);
    double BS_call = BS_Model(s, st_p, r_f, vola, t);
    
    cout << "Monte Carlo price: " << MC_call << "\n";
    cout << "Black-Scholes price: " << BS_call << "\n";
  

    return 0;
}
