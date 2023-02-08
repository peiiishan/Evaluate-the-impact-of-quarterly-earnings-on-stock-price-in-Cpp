//
//  Initializer.h
//  FinalProject
//
//  Created by Xingyuan Ding on 12/6/21.
//

#ifndef Initializer_h
#define Initializer_h

#include <map>
#include "Stock.h"
using namespace std;

class Initializer {
private:
    map<string, Stock> stockData;
    StockPrice benchmark;
    
    void populateSymbolVector(vector<string>& symbols);
    map<string, StockPrice> downloadStocksFromOnline();
    map<string, StockPrice> getStockPricesFromApi(vector<string>& symbol);
    void loadEarningInfo(map<string, EarningInfo>& earningInfos);
public:
    Initializer();
    map<string, Stock> getStockData() {
        return stockData;
    }
    StockPrice getBenchMark() {
        return benchmark;
    }
};

#endif /* Initializer_h */
