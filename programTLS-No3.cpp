#include <iostream>
using namespace std;

string getColor (int t) {
    int cycle =103;
    int rel = (t-45) % cycle;

    if (rel<0) rel += cycle;
    if (rel<0) return "yellow";
    else if (rel<83) return "red";
    else return "green";
    }
int main() {
    int times [] = {80,135,150,212};
    for (int t: times) {
        cout << "at second" << t << "->" << getColor(t) <<endl;
    }
}
    
