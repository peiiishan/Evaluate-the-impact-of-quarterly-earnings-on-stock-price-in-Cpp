//
//  Calculator.cpp
//  Team Project
//
//  Created by 张君陶 on 2021/12/8.
//

#include "Calculator.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;
//Vector AAR(const &matrix);

Vector operator-(const Vector& V, const Vector& W){
    int d = (int)V.size();
    Vector U(d);
    for(int i = 0;i<V.size();i++){
        U[i] = V[i] - W[i];
    }
    return U;
}

//====================================================

Vector operator+(Matrix &m, Vector &v){
    for (int i = 0;i<m[0].size();i++){
        double res = 0.0;
        for (int j = 0;j<m.size();j++){
            res += m[j][i];}
        v[i] = res/m.size();}
    return v;
}

Vector addition(Vector &AAR, double num){
    Vector v(AAR.size());
    for (int i=0;i<AAR.size();i++) {
        num += AAR[i];
        v[i] = num;
    }
    return v;
}

Vector AAR(Matrix &m){
    Vector v(m[0].size());
    return m+v;
}



Vector CAAR(Vector &AAR){
    double init = 0.0;
    return addition(AAR,init);
};


//---------------------------------

Vector mean(const Matrix &m2){
    Vector res(m2[0].size());
    for (int i=0;i<m2[0].size();i++) {
        double r=0.0;
        for (int j = 0;j<m2.size();j++){
            r+= m2[j][i];
        }
        res[i] = r/40;
    }
    return res;
}

Vector stdev(const Matrix &m2){
    Vector avg = mean(m2);
    Vector res(m2[0].size());
    for (int i=0;i<m2[0].size();i++) {
        double r=0.0;
        for (int j = 0;j<m2.size();j++){
            r+= pow(m2[j][i]-avg[i],2);
        }
        res[i] = sqrt(r/(40-1));
    }
    return res;
}
//-----------------------------
Matrix call_bootstrap(vector<Stock> stocks, StockPrice benchmark, int n) {
    Matrix output_AAR(40);
    Matrix output_CAAR(40);
    Matrix output(4);
    Bootstrap bootstrap;
    for (int i=0;i<40;i++) {
        Matrix m = bootstrap.bootstrapping(stocks,benchmark,n); //function that gives me a matrix with size 80*2N
        output_AAR[i]=AAR(m);
        output_CAAR[i]=CAAR(output_AAR[i]);
    }
    output[0] = mean(output_AAR);
    output[1] = stdev(output_AAR);
    output[2] = mean(output_CAAR);
    output[3] = stdev(output_CAAR);
    return output;
};
