#include "Initializer.h"
#include "Menu.h"
#include <iostream>
using namespace std;

int main(void)
{
    cout << "Start loading data..." << endl;
    Initializer initializer;
    //Load Russell 1000
    map<string, Stock> stockData = initializer.getStockData();
    
    //Load IWB
    StockPrice benchmark = initializer.getBenchMark();
    //Run menu
    menu mainmenu(&stockData,&benchmark);
    mainmenu.runmenu();
    
    
    return 0;
}
