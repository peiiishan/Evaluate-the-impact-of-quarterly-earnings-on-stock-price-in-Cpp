
//  Created by PeishanLiu on 2021-12-10.

#include"Gnuplot.hpp"

// Generate a matrix to store results for all 3 groups as required
vector<Matrix> get_computation_result(StockGroup groups,  StockPrice *benchmark, int N){
   
    vector<Matrix> plot_data;
    plot_data.push_back(call_bootstrap(groups.getBeat(),*benchmark, N));
    plot_data.push_back(call_bootstrap(groups.getMeet(),*benchmark, N));
    plot_data.push_back(call_bootstrap(groups.getMiss(),*benchmark, N));

    return plot_data;
}

void Gnuplot_CAAR(vector<Matrix> computation_result, int N){
    Vector caar_group1 = computation_result[0][2];
    Vector caar_group2 = computation_result[1][2];
    Vector caar_group3 = computation_result[2][2];
//    auto start = std::chrono::steady_clock::now();
      
    FILE *plotHandle = NULL;

    if (plotHandle == NULL)
    {
        plotHandle = popen("/opt/local/bin/gnuplot -persist", "w");
    }

    fprintf(plotHandle, "set term wx\n");
    fprintf(plotHandle, "set xlabel \"Day number\"\n");
    fprintf(plotHandle, "set ylabel \"AVG-CAAR\"\n");
    fprintf(plotHandle, "set title \"CAAR of the three groups\"\n");
    fprintf(plotHandle, "set grid\n");
    fprintf(plotHandle, "plot '-' using 1:2 with linespoints t 'BEAT', '-' using 1:2 with linespoints t 'MEET', '-' using 1:2 with linespoints t 'MISS'\n");
    for (int i = 0; i < caar_group1.size(); i++)
    {
        if (!isnan(caar_group1[i])) {
            fprintf(plotHandle, "%d %f\n", i-N, caar_group1[i]);
        }
    }
    fprintf(plotHandle, "%s\n", "e");
    cout << "#####################" << endl;
    for (int i = 0; i < caar_group2.size(); i++)
    {
        if (!isnan(caar_group2[i]) ) {
            fprintf(plotHandle, "%d %f\n", i-N, caar_group2[i]);
        }
    }
    fprintf(plotHandle, "%s\n", "e");
    cout << "#####################" << endl;
    for (int i = 0; i < caar_group3.size(); i++)
    {
        if (!isnan(caar_group3[i])) {
            fprintf(plotHandle, "%d %f\n", i-N, caar_group3[i]);
        }
    }

    fprintf(plotHandle, "%s\n", "e");

    fflush(plotHandle);
//    pclose(plotHandle);

//    auto end = std::chrono::steady_clock::now();
//    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//        std::cout << "case 1 : inline data for ploting. It took: " << elapsed.count() << " microseconds." << std::endl;
}
