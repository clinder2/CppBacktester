#include "DB.hpp"

vector<double> DB(vector<bar> series, int n) {
    double phi1=sample_acf(series, 1);
    cout<<phi1<<" DB\n";
    double v0 = s_autocovf(series, 0);
    //cout<<sm(series)<<" DB\n";
    vector<double> prev;
    prev.push_back(phi1);
    vector<double> autocov;
    autocov.push_back(s_autocovf(series, 1));
    double prev_v = v0;
    for (int i = 1; i<n; i++) {
        double gamma_n = s_autocovf(series, i+1);
        //cout<<gamma_n<<"\n";
        double phi_nn = gamma_n;
        for (int j = 0; j < i; j++) {
            phi_nn -= prev[j]*autocov[i-1-j];
        }
        phi_nn /= prev_v;
        for (int j = 0; j < i; j++) {
            prev[j]-=phi_nn*prev[i-1-j];
        }
        prev.push_back(phi_nn);
        autocov.push_back(gamma_n);
        prev_v *= (1-phi_nn*phi_nn);
        //cout<<phi_nn<<", "<<gamma_n<<" db\n";
    }
    return prev;
}