//
//  Stock.h
//  FinalProject
//
//  Created by Xingyuan Ding on 12/3/21.
//

#ifndef Stock_h
#define Stock_h

#include <string>
#include <vector>
#include "Utils.h"
using namespace std;

enum SurprisingGroup{BEAT=1, MISS=2, MEET=3};

struct StockPrice {
    vector<string> dates;
    vector<double> prices;
};

struct EarningInfo {
    string earningDate;
    string periodEndDate;
    double estimate;
    double reported;
    double surprise;
    double surprisePercentage;
};

class Stock {
private:
    string ticker;
    StockPrice stockPrice;
    EarningInfo earningInfo;
    int earningDateIndex;
public:
    Stock(){};
    Stock(string ticker, StockPrice stockPrice, EarningInfo earningInfo);

    vector<double> getprice(){return stockPrice.prices;}
    double getSurprisePercentage(){return earningInfo.surprise;}
    vector<double> calculateCumulativeDailyReturn() const;
    vector<double> calculateDailyReturn(const int n) const;
    vector<double> calculateAbnormalDailyRetrun(const StockPrice& benchmark, const int n) const;
    void displayInformation() const;
};

#endif /* Stock_h */
