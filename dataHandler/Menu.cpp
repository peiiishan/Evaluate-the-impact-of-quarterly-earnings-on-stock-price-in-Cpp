//
//  Menu.cpp
//  Created on 12/12/21.
//
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include "Menu.h"
#include <string>
#include <cmath>

using namespace std;
int getInput(){
    cout<<"=======Menu======="<<endl;
    cout << "- Enter N (Default is 60) (enter 1)" << endl
    << "- Pull information for one stock from one group (enter 2)" << endl
    << "- Show AAR, AAR-SD, CAAR and CAAR-STD for one group (enter 3)" << endl
    << "- Show the gnuplot graph with CAAR for all 3 groups (enter 4)" << endl
    << "- Exit (enter 5)" << endl << endl
    << "Enter your choice: ";
    int input;
    cin >> input;
    cout << endl;
    return input;
}
void getGroup(int &group){
    cout << "Select the group: " << endl
        << "1. Beat Estimate Group" << endl
        << "2. Meet Estimate Group" << endl
        << "3. Miss Estimate Group" << endl << endl
        << "Enter your choice: ";
    cin >> group;
    cout << endl;
}


void menu::runmenu(){
    map<int, string> groupname;
    groupname[1] = "Beat";
    groupname[2] = "Meet";
    groupname[3] = "Miss";
    
    while(1){
        int opt; // Variable holds the user chioce
        cout << endl;
        //display menu and get input
        opt = getInput();
        
        if(opt==1){
            int N;
            cout << "Enter N: ";
            cin >> N;
            while(N<60 || N>100){
                cout << "You entered an invalid number. Please re-enter a number between 60-100: ";
                cin >> N;
            }
            SetN(N);
            cout << "The N you entered is: " << N << endl;
        } else if(opt==2){
            string ticker;
            cout << "Enter stock ticker: ";
            cin >> ticker;
            cout << endl;
            while(stockData->count(ticker)<=0){
                cout << "You entered an invalid ticker. Please re-enter a ticker: ";
                cin >> ticker;
                cout << endl;
            }
            cout << "#########Information######### " << endl;
            if((*stockData)[ticker].getSurprisePercentage()>=threshold[0]){
                cout << "Group belong to: Beat" << endl;
            } else if ((*stockData)[ticker].getSurprisePercentage()>=threshold[1]){
                cout << "Group belong to: Meet" << endl;
            } else{
                cout << "Group belong to: Miss" << endl;
            }
            (*stockData)[ticker].displayInformation();
            
        } else if(opt==3){
            int group;
            getGroup(group);
            while(group < 1 || group > 3){
                cout << "You entered an invalid number." << endl << endl;
                getGroup(group);
            }
            cout << "The group you entered is: " << groupname[group] << endl << endl;
            cout << setw(6) << "Average AAR"
             << setw(13) << "AAR STD"
             << setw(17) << "Average CAAR"
             << setw(13) << "CAAR STD"
             << endl;
            
            Matrix stat;
            if(group == 1){
                stat = call_bootstrap(groups.getBeat(),*benchmark, N);
            } else if(group == 2){
                stat = call_bootstrap(groups.getMeet(),*benchmark, N);
            } else{
                stat = call_bootstrap(groups.getMiss(),*benchmark, N);
            }
            
            for (int i = 0; i < stat[0].size(); i++)
                        {

                            cout << fixed << setprecision(6)<< setw(6) << stat[0][i]
                                << setw(15) << stat[1][i]
                                << setw(15) << stat[2][i]
                                << setw(15) << stat[3][i]
                                << endl;
            }
            
            

        } else if(opt==4){
            // Get the expected AAR, AARSTD, CAAR, CAARSTD for 3 groups of stocks in one matrix
            vector<Matrix> computation_result = get_computation_result(groups, benchmark, N);
            // Method for plotting
            Gnuplot_CAAR(computation_result, N);
        } else if(opt==5){
            cout << "Exit program." << endl;
            break;
        } else{
            cout << " You entered an invalid number. Please re-enter a number between 1-5" << endl;
        }
        cout << endl;
    }

    
}
void menu::Clear(){
    delete stockData;
    delete benchmark;
    stockData = NULL;
    benchmark = NULL;
}
