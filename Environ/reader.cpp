#include </Users/christopherlinder/Desktop/CppBacktester/Environ/reader.hpp>
#include <cstddef>
//#include </Users/christopherlinder/Desktop/CppBacktester/yfinance-cpp-main/cpp/base.cpp>
//#include <boost/version.hpp>

/* map<string, map<string, double> > _pull_process_symbols_from_csv(string file_path, vector<string>* symbol_list) {
            
} */

/* int main() {
    reader r;

    vector<string> sym;
    sym.push_back("AAPL");
    sym.push_back("IONQ");
    sym.push_back("NVDA");

    r._pull_process_symbols_from_csv("/Users/christopherlinder/Desktop/CppBacktester/HistoricData/test.csv", &sym);
    ifstream file("/Users/christopherlinder/Desktop/CppBacktester/HistoricData/test.csv");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> row;
        cout<<line<<"end \n";

        while (getline(ss, token, ',')) {
            //cout<<token<<" end\n";
            row.push_back(token);
        }

        for (const string& cell : row) {
            //cout<<cell<<" \n";
        }
    }
    file.close();
    return 0;
} */