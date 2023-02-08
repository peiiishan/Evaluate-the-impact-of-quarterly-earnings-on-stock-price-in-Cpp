//
//  Bootstrap.hpp
//  6883FinalProject
//
//  Created by 张环欣 on 2021-12-10.
//

#ifndef Bootstrap_hpp
#define Bootstrap_hpp

#include <stdio.h>
#include <vector>
#include "Stock.h"
#include <iostream>
#include <vector>
#include <random>
#include <map>

using namespace std;
class Bootstrap {
private:
    default_random_engine m_random;
public:
    Bootstrap();
    vector<vector<double>> bootstrapping(vector<Stock> stocks,const StockPrice& benchmark, const int n);
};


#endif /* Bootstrap_hpp */
