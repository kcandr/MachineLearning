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
vector<string> attributeNames;
vector<int> Q;

struct Node {
    string attrName;
    Node *left, *right;
};

int read()
{
    ifstream input("input.txt");
    if ( !input ) {
        return 1;
    }

    input >> attributeCount;
    input >> cortegeCount;
    string attrName;
    
    for (int i = 0; i < attributeCount; ++i) {
        input >> attrName;
        attributeNames.push_back(attrName);
    }
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
    for (int i = 0; i < attributeCount-1; ++i) {
        Q.push_back(i);
    }
    S = table.at(0).size() - 1;
    return 0;
}

bool checkAllTrue(const vector<vector<int> > &params)
{
    for (int i = 0; i < params.size(); ++i) {
        if ( !params.at(i).at(S) ) {
            return false;
        }
    }
    return true;
}

bool checkAllFalse(const vector<vector<int> > &params)
{
    for (int i = 0; i < params.size(); ++i) {
        if ( params.at(i).at(S) ) {
            return false;
        }
    }
    return true;
}

bool checkTrue(const vector<vector<int> > &params)
{
    int pos = 0;
    for (int i = 0; i < params.size(); ++i) {
        if ( params.at(i).at(S) ) {
            ++pos;
        }
    }
    if (pos > cortegeCount / 2) {
        return true;
    } else {
        return false;
    }
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
        return 0;
    }
    return -pk * (log( pk ) / log( 2.0 )) - 
            nk * (log( nk ) / log( 2.0 ));
}

double gain(const vector<vector<int> > &params, const int target)
{
    vector<vector<int> > positiveSub;
    vector<vector<int> > negativeSub;
    
    for (int i = 0; i < params.size(); ++i) {
        if ( params.at(i).at(target) ) {
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

int maxGain(const vector<vector<int> > &params, vector<int> Q)
{
    double max = -1;
    double infGain = 0;
    int tgt = -1;
    for (int i = 0; i < Q.size(); ++i) {
        infGain = gain(params, Q.at(i));
        if ( max < infGain ) {
            max = infGain;
            tgt = i;
        }
    }
    return tgt;
}

Node* learnID3(const vector<vector<int> > &params, vector<int> Q)
{
    Node *node = new Node();
    if ( checkAllTrue(params) ) {
        node->attrName = "WIN";
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    if ( checkAllFalse(params) ) {
        node->attrName = "LOSE";
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    if ( Q.empty() ) {
        node->left = NULL;
        node->right = NULL;
        if ( checkTrue(params) ) {
            node->attrName = "1";
        } else {
            node->attrName = "0";
        }
        return node;
    }

    int QS = maxGain(params, Q);
    int qq = Q.at(QS);
    Q.erase(Q.begin() + QS);
    vector<vector<int> > positiveSub;
    vector<vector<int> > negativeSub;

    for (int i = 0; i < params.size(); ++i) {
        if ( params.at(i).at(qq) ) {
            positiveSub.push_back(params.at(i));
        } else {
            negativeSub.push_back(params.at(i));
        }
    }
    node->attrName = attributeNames.at(qq);
    node->left = learnID3(negativeSub, Q);
    node->right = learnID3(positiveSub, Q);
    
    return node;
}

void Show(Node *pTemp, int level)
{
    if (pTemp != NULL)
    {
        Show(pTemp->right, level + 1);
        for (int i = 0; i < level; ++i)
            cout << "\t";
        cout << pTemp->attrName << endl;
        Show(pTemp->left, level + 1);
    }
}
int main()
{
    read();

    Node *root = NULL;
    root = learnID3(table, Q);
    Show(root, 0);

    return 1;
}