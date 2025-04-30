#ifndef READER_H
#define READER_H

#include <iostream>
#include <string>
#include <curl/curl.h>
//#include <boost>
#include <vector>
#include <sstream>

using namespace std;

class reader {
    virtual void stock(string ticker);
};

#endif