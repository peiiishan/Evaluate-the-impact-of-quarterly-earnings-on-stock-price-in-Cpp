//
//  Utils.cpp
//  FinalProject
//
//  Created by Xingyuan Ding on 12/6/21.
//

#include "Utils.h"
using namespace std;

int write_data(void* ptr, int size, int nmemb, FILE* stream)
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void *myrealloc(void *ptr, size_t size)
{
    if (ptr)
        return realloc(ptr, size);
    else
        return malloc(size);
}

int write_data2(void *ptr, size_t size, size_t nmemb, void *data)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)data;
    mem->memory = (char *)myrealloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory) {
        memcpy(&(mem->memory[mem->size]), ptr, realsize);
        mem->size += realsize;
        mem->memory[mem->size] = 0;
    }
    return realsize;
}

vector<double> calculate_daily_returns(const vector<double>& prices, int index, int n) {
    vector<double> dailyReturns;
    for (int i = index - n + 1; i <= index + n; i++) {
        // Handling data missing
        // Prepending and appending default value 0 when input n is out of the scope of price data length
        if (i < 1 || i > prices.size())
            dailyReturns.push_back(0);
        else
            dailyReturns.push_back(prices[i]/prices[i-1]-1);
    }
    return dailyReturns;
}
/*vector<double> calculate_daily_returns(const vector<double>& prices, int index, int n) {
    vector<double> dailyReturns;
    for (int i = index-1; i >= index - n + 1; i--) {
            dailyReturns.push_back(prices[i]/prices[i+1]-1);
    }
    dailyReturns.push_back(0);
    for (int i = index+1; i <= index + n; i++) {
            dailyReturns.push_back(prices[i]/prices[i-1]-1);
    }
    
    return dailyReturns;
}*/
string TranslateDate(string raw) {
    int strlength = (int)raw.size();
    string day = raw.substr(0, strlength - 7);
    string monthandyear = raw.substr(strlength - 6, strlength);
    string month = monthandyear.substr(0, 3);
    string year = monthandyear.substr(4, monthandyear.size());
    string str;
    str.append("20");
    str.append(year);
    str.append("-");
    string mm;
    if (month == "Mar") {
        mm = "03";
    }
    else if (month == "Apr") {
        mm = "04";
    }
    else if (month == "May") {
        mm = "05";
    }
    else {
        mm = "06";
    }
    str.append(mm);
    str.append("-");
    if (day.size() == 2) {
        str.append(day);
    }
    else {
        str.append("0");
        str.append(day);
    }
    return str;
}


