#include "LogisticRegression.h"

#include <iostream>
#include <fstream>
#include <math.h>

LogisticRegression::LogisticRegression(void)
{
}

int LogisticRegression::readData(const std::string& fileName)
{
    std::ifstream input( fileName );
    if ( !input ) {
        return 1;
    }

    input >> attributeCount;
    input >> cortegeCount;
    std::string attrName;

    for ( int i = 0; i < attributeCount; ++i ) {
        input >> attrName;
        attributeNames.push_back( attrName );
    }

    double tmpData;
    std::vector<double> tmpVector;
    for ( int i = 0; i < cortegeCount; ++i ) {
        tmpVector.push_back(1.0);
        for ( int j = 0; j < attributeCount - 1; ++j ) {
            input >> tmpData;
            tmpVector.push_back( tmpData );
        }
        data.push_back( tmpVector );
        tmpVector.clear();

        input >> tmpData;
        predictedData.push_back( tmpData );
    }

    return 0;
}

double LogisticRegression::sigmoid(double x)
{
    return 1.0 / ( 1.0 + exp( -x ) );
}

double LogisticRegression::computeDot(std::vector<double> x, std::vector<double> theta)
{
    double sum = 0;
    for ( unsigned int i = 0; i < x.size(); ++i ) {
        sum += x[i] * theta[i];
    }
    return sum;
}

double LogisticRegression::computeCost(std::vector<std::vector<double> > x, 
                                       std::vector<double> y, 
                                       std::vector<double> theta)
{
    double h = 0;
    double J = 0;
    double m = y.size();

    for ( unsigned int i = 0; i < data.size(); ++i ) {
        h = sigmoid( computeDot( x[i], theta ) );
        J += y[i] * log( h ) + ( 1.0 - y[i] ) * log( 1.0 - h );
    }
    return ( -1.0 / m ) * J; 
}

void LogisticRegression::printTheta()
{
    std::cout << "Theta:" << std::endl;
    for( unsigned int i = 0; i < this->theta.size(); ++i ) {
        std::cout << this->theta[i] << std::endl;
    }
    std::cout << std::endl;
}

void LogisticRegression::gradientDescent(const double alpha, const int iterationsCount)
{
    std::vector<double> J_history;
    J_history.reserve(10000);
    int m = this->predictedData.size();

    for ( int i = 0; i < attributeCount; ++i ) {
        this->theta.push_back(0);
    }

    double zeroCost = computeCost(this->data, this->predictedData, this->theta);

    double J = 0;
    for(int iter = 0; iter < iterationsCount; iter++) {
        std::cout << "Iter " << iter + 1 << ": ";

        // then compute the error and update the theta
        double error = 0;
        double h = 0;
        double grad = 0;
        for( unsigned int i = 0; i < this->theta.size(); ++i ) {
            std::vector<double> diff;
            std::vector<double> X_col;
            for( unsigned int j = 0; j < this->data.size(); ++j ) {
                double val = computeDot(this->data[j], this->theta);
                h = sigmoid(val);

                diff.push_back(h - this->predictedData[j]);
                X_col.push_back(this->data[j][i]);
            }
            error = computeDot(diff, X_col);
            grad = (1.0 / m) * error;

            // update the theta
            this->theta[i] = this->theta[i] - alpha * grad;
        }

        J = computeCost(this->data, this->predictedData, this->theta);
        std::cout << J << std::endl;
        J_history.push_back(J);
    }
    std::cout << std::endl;
    std::cout << "Cost at initial theta (zeros): " << zeroCost << std::endl;
    std::cout << "Cost at theta found by gradient descent: " << J_history[J_history.size() - 1] << std::endl;
    printTheta();
}

LogisticRegression::~LogisticRegression(void)
{
}
