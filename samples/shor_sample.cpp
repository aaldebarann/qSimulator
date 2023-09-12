#include <iostream>
#include "shor.h"
using namespace std;

int main() {
    unsigned N;
    cout << "enter a number"<<endl;
    cin >> N;
    cout << shor_classic(N)<<" is a divider"<<endl;
    return 0;
}
