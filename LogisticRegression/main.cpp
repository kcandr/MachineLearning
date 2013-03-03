#include <iostream>
#include <conio.h>
#include "LogisticRegression.h"

int main()
{
    double alpha = 0.001;
    int iters = 10000;
    LogisticRegression lr;

    lr.readData("input.txt");
    lr.gradientDescent(alpha, iters);
    
    int n = _getch();
    return 1;
}