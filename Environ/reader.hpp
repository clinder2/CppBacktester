#ifndef READER_H
#define READER_H

#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>
//#include <boost>
#include <vector>
#include <map>
#include <queue>
#include <sstream>
#include <ctime>
#ifndef boost
//#include "boost/coroutine2/all.hpp"
#endif
#include </Users/christopherlinder/Desktop/CppBacktester/Environ/event.hpp>

using namespace std;

class reader {
    public:
        /* queue<event> events;
        string start;
        string end;
        vector<string> symbol_list;
        map<string, map<string, float> > symbol_data;
        map<string, map<string, float> > latest_symbol_data;
        bool continue_backtest; */
        //virtual void stock(string ticker);
        map<string, map<long, map<string, double> > > _pull_process_symbols_from_csv(string file_path, vector<string>* symbol_list) {
            map<string, map<long, map<string, double> > > symbol_data; // ticker->index->prop->value
            ifstream file(file_path);
            string line;

            getline(file, line);
            //cout<<line<<"end\n";
            getline(file, line);
            //cout<<line<<"end\n";
            getline(file, line);

            while (getline(file, line)) {
                replace(line.begin(),line.end(),',',' ');
                vector<string> data;
                stringstream ss(line);

                tm time = {};
                string temp;
                ss >> temp;
                istringstream t(temp);
                t>>get_time(&time, "%Y-%m-%d");
                time_t epochtime = mktime(&time);
                int mod = symbol_list->size();

                for (int i = 0; i < mod; i++) {
                    string ticker = (*symbol_list)[i];
                    ss>>symbol_data[ticker][epochtime]["Close"];
                    //cout<<ticker<<" end\n";
                }

                for (int i = 0; i < mod; i++) {
                    string ticker = (*symbol_list)[i];
                    ss>>symbol_data[ticker][epochtime]["High"];
                }

                for (int i = 0; i < mod; i++) {
                    string ticker = (*symbol_list)[i];
                    ss>>symbol_data[ticker][epochtime]["Low"];
                }
                for (int i = 0; i < mod; i++) {
                    string ticker = (*symbol_list)[i];
                    ss>>symbol_data[ticker][epochtime]["Open"];
                }
                for (int i = 0; i < mod; i++) {
                    string ticker = (*symbol_list)[i];
                    ss>>symbol_data[ticker][epochtime]["Volume"];
                    //cout<<symbol_data[ticker][epochtime]["Volume"]<<" v end\n";
                }

                //cout<<epochtime<<"end\n";
            }

            return symbol_data;
        }
};

#endif