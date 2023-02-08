//  Created by PeishanLiu on 2021-12-10.

#ifndef Gnuplot_hpp
#define Gnuplot_hpp

#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <vector>
#include "Calculator.hpp"
#include "StockGroup.h"
#include "Stock.h"
using namespace std;

vector<Matrix> get_computation_result(StockGroup groups,  StockPrice *benchmark, int N);
void Gnuplot_CAAR(vector<Matrix> computation_result, int n);


#endif /* Gnuplot_hpp */
