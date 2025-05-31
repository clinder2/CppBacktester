#include "sampleACF.hpp"

int main() {
    vector<bar> b;
    double arr[] = {.01,	-.02,	.03,	-.04,	.06,	.02,	-.01,	-.03,	.04};
    
    for (int i = 0; i < 9; i++) {
        bar b1;
        b1.close = arr[i];
        b.push_back(b1);
    }
    cout<<s_autocovf(b, 1)<<"\n";
    return 0;
}