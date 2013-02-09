#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

int attributeCount;
int cortegeCount;
int S;
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
    S = table.at(0).size() - 1;
    return 0;
}

double entropy(const vector<vector<int> > &params, int target)
{
    double positive = 0;
    double negative = params.size();

    int count = params.size();
    for (int i = 0; i < count; ++i) {
        if ( params.at(i).at(target) ) {
            ++positive;
        }
    }
    negative -= positive;
    double pk = positive / count;
    double nk = negative / count;

    if ( positive == 0) {
        return 0;
    };
    if ( negative == 0) {
        return 1;
    }
    return -pk * (log( pk ) / log( 2.0 )) - 
            nk * (log( nk ) / log( 2.0 ));
}

double gain(const vector<vector<int> > &params, int Q)
{
    vector<vector<int> > positiveSub;
    vector<vector<int> > negativeSub;
    
    for (int i = 0; i < params.size(); ++i) {
        if ( params.at(i).at(Q) ) {
            positiveSub.push_back(params.at(i));
        } else {
            negativeSub.push_back(params.at(i));
        }
    }
    double pk = (double) positiveSub.size() / params.size();
    double nk = (double) negativeSub.size() / params.size();

    return entropy(params, S) - pk * entropy(positiveSub, S) 
                              - nk * entropy(negativeSub, S);
}

int main()
{
    read();
    cout << gain(table, 1);
    return 0;
}