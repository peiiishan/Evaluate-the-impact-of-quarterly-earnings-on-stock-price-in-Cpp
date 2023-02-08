//
//  Menu.h
//  Created on 12/12/21.
//

#ifndef Menu_h
#define Menu_h


#endif /* Menu_h */
#include "Initializer.h"
#include "Stock.h"
#include "Bootstrap.hpp"
#include "Calculator.hpp"
#include "StockGroup.h"
#include "Gnuplot.hpp"
using namespace std;

class menu{
private:
    int N;
    map<string, Stock> *stockData;
    StockGroup groups;
    StockPrice *benchmark;
    vector<double> threshold;
public:
    menu(map<string, Stock> *stockData_, StockPrice *benchmark_):N(60),stockData(stockData_),benchmark(benchmark_){threshold = groups.setStockGroup(*stockData);};
    void SetN(int N_) {N = N_;};
    void runmenu();
    void Clear();
};
