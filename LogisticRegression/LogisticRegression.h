#ifndef LOGISTICREGRESSION_H
#define LOGISTICREGRESSION_H

#include <string>
#include <vector>

class LogisticRegression
{
public:
    LogisticRegression(void);
    ~LogisticRegression(void);

    int readData(const std::string& fileName);
    void gradientDescent(const double alpha, const int iterationsCount);

private:
    unsigned int attributeCount;
    unsigned int cortegeCount;
    std::vector<std::string> attributeNames;
    std::vector<std::vector<double> > data;
    std::vector<double> predictedData;
    std::vector<double> theta;

    double computeCost(std::vector<std::vector<double> > x, 
                       std::vector<double> y, 
                       std::vector<double> theta);
    double sigmoid(double x);
    double computeDot(std::vector<double> x, std::vector<double> theta);
    void printTheta();
    void printData();
};

#endif //LOISTICREGRESSION_H