#include "LOB.cpp"
#include <iostream>

int main() {
    HM_LOB h;
    h.add(*(new orderEvent("a" ,"a", 0, "a")));
    cout<<"a";
    return 0;
}