//
//  StockGroup.h
//  FinalProject
//
//  Created by Hanlu Ni on 12/10/21.
//
#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <map>
//#include <algorithm> //for sort function
#include "Stock.h"



using namespace std;

class StockGroup {
private:
	vector<Stock> beat;
	vector<Stock> meet;
	vector<Stock> miss;
public:
    vector<double> setStockGroup(map<string, Stock> &mymap);
	vector<Stock> getBeat() { return beat; }
	vector<Stock> getMeet() { return meet; }
	vector<Stock> getMiss() { return miss; }
};
