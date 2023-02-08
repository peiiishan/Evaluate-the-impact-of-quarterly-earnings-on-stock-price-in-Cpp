//
//  Initializer.cpp
//  FinalProject
//
//  Created by Xingyuan Ding on 12/6/21.
//
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include "curl/curl.h"
#include "Initializer.h"
#include "Stock.h"
#include "Utils.h"

using namespace std;

const char* cIWB1000SymbolFile = "Russell_1000_component_stocks.csv";
const char* earningAnnouncementFile = "EarningsAnnouncements (duplicate removed).csv";

void Initializer::populateSymbolVector(vector<string>& symbols)
{
    ifstream fin;
    fin.open(cIWB1000SymbolFile, ios::in);
    string line, name, symbol;
    while (!fin.eof())
    {
        getline(fin, line);
        stringstream sin(line);
        getline(sin, symbol, ',');
        getline(sin, name);
        symbols.push_back(symbol);
    }
}

void Initializer::loadEarningInfo(map<string, EarningInfo>& earningInfos) {
    string line;
    ifstream f(earningAnnouncementFile);
    bool isFirstLine = true;
    if (f.is_open())
    {
        while (getline(f,line))
        {
            if (isFirstLine) {
                isFirstLine = false;
                continue;
            }
            vector<string> seglist;
            stringstream ss(line);
            string segment;
            while (getline(ss, segment, ','))
            {
               seglist.push_back(segment);
            }
            earningInfos.insert({seglist[0], {seglist[1],seglist[2],stod(seglist[3]),stod(seglist[4]),stod(seglist[5]),stod(seglist[6])}});
        }
    }
}

map<string, StockPrice> Initializer::downloadStocksFromOnline()
{
    vector<string> symbolList;
    populateSymbolVector(symbolList);
    return getStockPricesFromApi(symbolList);
}

map<string, StockPrice> Initializer::getStockPricesFromApi(vector<string>& symbols) {
    CURL* handle;
    CURLcode result;
    curl_global_init(CURL_GLOBAL_ALL);
    map<string, StockPrice> stockPriceMap;
    handle = curl_easy_init();
    curl_easy_setopt(handle, CURLOPT_USERAGENT,"Mozilla/5.0(Windows NT 10.0; Win64; x64; rv:74.0) Gecko/20100101Firefox/74.0");
    curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
    if (handle)
    {
        string url_common = "https://eodhistoricaldata.com/api/eod/";
        string start_date = "2020-12-01";
        string end_date = "2021-11-30";
        string api_token = "61aeb5a8def104.22282854";
        
        for (vector<string>::iterator iter = symbols.begin(); iter != symbols.end(); iter++) {
            struct MemoryStruct data;
            data.memory = NULL;
            data.size = 0;
            vector<string> dates;
            vector<double> prices;
            string symbol = *iter;
            string url_request = url_common + symbol + ".US?" + "from=" + start_date + "&to=" + end_date + "&api_token=" + api_token + "&period=d";
            curl_easy_setopt(handle, CURLOPT_URL,url_request.c_str());
            curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&data);
            result = curl_easy_perform(handle);
            if (result != CURLE_OK)
            {
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(result));
                throw runtime_error("curl_easy_perform() failed");
            }
            stringstream sData;
            sData.str(data.memory);
            string sValue, sDate;
            double dValue = 0;
            string line;
            while (getline(sData, line)) {
                size_t found = line.find('-');
                if (found != std::string::npos)
                {
                    sDate = line.substr(0, line.find_first_of(','));
                    line.erase(line.find_last_of(','));
                    sValue = line.substr(line.find_last_of(',') + 1);
                    dValue = strtod(sValue.c_str(), NULL);
                    dates.push_back(sDate);
                    prices.push_back(dValue);
                }
            }
            stockPriceMap.insert({symbol, {dates, prices}});
            free(data.memory);
            data.size = 0;
        }
    } else {
        fprintf(stderr, "Curl init failed!\n");
        throw runtime_error("Curl init failed!");
    }
    curl_easy_cleanup(handle);
    curl_global_cleanup();
    return stockPriceMap;
}

Initializer::Initializer() {
    map<string, StockPrice> stockPrices = downloadStocksFromOnline();
    map<string, EarningInfo> earningInfos;
    loadEarningInfo(earningInfos);
    for (map<string, StockPrice>::iterator stockPriceIter = stockPrices.begin(); stockPriceIter != stockPrices.end(); stockPriceIter++) {
        string ticker = stockPriceIter->first;
        map<string, EarningInfo>::iterator earningInfoIter = earningInfos.find(ticker);
        if (earningInfoIter != earningInfos.end()) {
            StockPrice stockPrice = stockPriceIter->second;
            EarningInfo earningInfo = earningInfoIter->second;
            Stock stock(ticker, stockPrice, earningInfo);
            stockData.insert({ticker, stock});
        }
    }
    vector<string> vect;
    vect.push_back("IWB");
    benchmark = getStockPricesFromApi(vect)["IWB"];
}
