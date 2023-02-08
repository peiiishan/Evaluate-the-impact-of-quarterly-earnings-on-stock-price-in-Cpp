//
//  Stock.cpp
//  FinalProject
//
//  Created by Xingyuan Ding on 12/6/21.
//
#include <iostream>
#include <iomanip>
#include "Stock.h"
#include "Calculator.hpp"
using namespace std;
Stock::Stock(string ticker, StockPrice stockPrice, EarningInfo earningInfo): ticker(ticker), stockPrice(stockPrice), earningInfo(earningInfo) {
    earningDateIndex = 0;
    for (vector<string>::iterator iter = stockPrice.dates.begin(); iter != stockPrice.dates.end(); iter++) {
        if (iter->compare(TranslateDate(earningInfo.earningDate)) == 0) {
            break;
        } else {
            earningDateIndex += 1;
        }
    }
}
vector<double> Stock::calculateCumulativeDailyReturn() const {
    vector<double> cumulativeReturns;
    double prevReturnSum = 0;
    for (int i = 1; i < stockPrice.prices.size(); i++) {
        cumulativeReturns.push_back(prevReturnSum);
        prevReturnSum += stockPrice.prices[i]/stockPrice.prices[i-1] - 1;
    }
    cumulativeReturns.push_back(prevReturnSum);
    return cumulativeReturns;
}

vector<double> Stock::calculateDailyReturn(const int n) const {
    return calculate_daily_returns(stockPrice.prices, earningDateIndex, n);
}


vector<double> Stock::calculateAbnormalDailyRetrun(const StockPrice& benchmark, const int n) const {
    return calculate_daily_returns(stockPrice.prices, earningDateIndex, n) - calculate_daily_returns(benchmark.prices, earningDateIndex, n);
}

void Stock::displayInformation() const {
    cout << "Earning Announcement Date: " << earningInfo.earningDate << endl;
    cout << "Period Ending: " << earningInfo.periodEndDate << endl;
    cout << "Estimated Earnings: " << earningInfo.estimate << endl;
    cout << "Reported Earnings: " << earningInfo.reported << endl;
    cout << "Surprise: " << earningInfo.surprise << endl;
    cout << "Surprise %: " << earningInfo.surprisePercentage << "%" << endl << endl;
    cout << "#########Daily Prices######### " << endl;
    for(int i = 0;i<stockPrice.prices.size();i++){
        cout << fixed << setprecision(2) << stockPrice.dates[i] << ": " << stockPrice.prices[i] << endl;
    }
    cout << endl;
    cout << "#########Cumulative Daily Returns######### " << endl;
    vector<double> cum = calculateCumulativeDailyReturn();
    for(int i = 0;i<stockPrice.prices.size();i++){
        cout << fixed << setprecision(2) << stockPrice.dates[i] << ": " << cum[i] << endl;
    }
}
