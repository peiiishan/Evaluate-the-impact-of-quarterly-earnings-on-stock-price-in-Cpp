//
//  StockGroup.cpp
//  FinalProject
//
//  Created by Hanlu Ni on 12/10/21.
//
#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <algorithm> //for sort function
#include "Stock.h"
#include "StockGroup.h"
#include <ctime>

using namespace std;

//want to compair the surprisePercentage of two pair<string,Stock>
bool cmp(pair<string, Stock>& a, pair<string, Stock>& b) { return a.second.getSurprisePercentage() > b.second.getSurprisePercentage(); }

vector<double> StockGroup::setStockGroup(map<string, Stock> &mymap) {
    vector<pair<string, Stock>> A;
    map<string, Stock>::iterator itr;
    for (itr = mymap.begin(); itr != mymap.end(); itr++) {
        A.push_back(make_pair(itr->first, itr->second));
    }

    sort(A.begin(), A.end(), cmp);

    int count = 0;
    int a = (int)A.size()/3;
    int b = a*2;
    for (int i = 0; i < A.size(); i++) {
        if (count <= a) {
            beat.push_back(A[i].second);
        }
        else if (count <= b) {
            meet.push_back(A[i].second);
        }
        else {
            miss.push_back(A[i].second);
        }
        count++;
    }
    vector<double> group;
    group.push_back(A[a].second.getSurprisePercentage());
    group.push_back(A[b].second.getSurprisePercentage());
    return group;
}
