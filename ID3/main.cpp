#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

int attributeCount;
int cortegeCount;
vector<vector<int> > table;

int read()
{
    ifstream input("input.txt");
    if(!input)
        return 1;
    input >> attributeCount;
    input >> cortegeCount;
    int tmpInt;
    vector<int> tmpVector;
    for (int i = 0; i < cortegeCount; ++i) {
        for (int j = 0; j < attributeCount; ++j) {
            input >> tmpInt;
            tmpVector.push_back(tmpInt);
        }
        table.push_back(tmpVector);
        tmpVector.clear();
    }
    return 0;
}

double entropy()
{
    double positive = 0;
    double negative = cortegeCount;

    for (int i = 0; i < cortegeCount; ++i) {
        if ( table[i][attributeCount] ) {
            ++positive;
        }
    }
    negative -= positive;
    return -(positive / cortegeCount) * (log( positive ) / log( 2.0 )) - 
        (negative / cortegeCount) * (log( negative ) / log( 2.0 ));
}

int gain()
{
    return 1;
}

int main()
{
    read();
    cout << table[0][0];
    return 0;
}