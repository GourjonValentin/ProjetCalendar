//
// Created by valen on 10/11/2023.
//

#include "testing.h"
#include "list.h"
#include "timer.h"
#include "plot/pbPlots.h"
#include "plot/supportLib.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Test protocol :
// 1. Create a list of size 16
// 2. Search for a random value in the list
// 3. Repeat 2. 1000 times / 10000 times / 100000 times

// function that execute the above protocol for a given search function
time_result** test_search_time_for_given_func(t_d_list *list, int (*search_function)(t_d_list *, int)) {

    time_result **results = malloc(sizeof(time_result) * 3);

    for (int i = 0; i < 3; i++) {
        time_result * res = malloc(sizeof(time_result));
        double mean = 0;
        int n = 1000 * pow(10, i);
        res->n = n;

        for (int j = 0; j < n; j++) {
            int value = rand() % (int)(pow(2, list->max_levels) - 1);
            startTimer();
            search_function(list, value);
            stopTimer();
            mean += getTimeAsMsecs();
        }
        printf("Total time for n = %d : %f\n", n, mean);
        res->total_time = mean;

        mean /= n;
        printf("Mean time for n = %d : %f\n", n, mean);
        res->mean_time = mean;
        printf("\n");

        results[i] = res;
    }
    return results;
}

void test_search_time(int n_levels) {
    t_d_list *L;
    time_result** classic_results, **optimized_results;
    L = create_filled_list(n_levels);
    //print_aligned_list(L);

    printf("Comparing search time for classic and optimized search algorithms for a list of size %d\n", n_levels);
    printf("Times are in milliseconds\n");
    printf("\n");
    printf("Classic search: \n");
    classic_results = test_search_time_for_given_func(L, &classic_search);
    printf("\n");
    printf("Optimized search: \n");
    optimized_results = test_search_time_for_given_func(L, &optimized_search);

    // Ploting data using pbPlots library

    // Creating data
    printf("Creating data...\n");

    double *x = malloc(sizeof(int) * 3);
    double *y1 = malloc(sizeof(double) * 3);
    double *y2 = malloc(sizeof(double) * 3);

    for (int i = 0; i < 3; i++) {
        x[i] = classic_results[i]->n;
        y1[i] = optimized_results[i]->total_time;
        y2[i] = classic_results[i]->total_time;
    }

    // Plotting data
    printf("Plotting data...\n");

    _Bool success;
    StringReference *errorMessage;

    double xs [] = {-2, -1, 0, 1, 2};
    double ys [] = {2, -1, -2, -1, 2};

    StartArenaAllocator();

    ScatterPlotSeries *series1 = GetDefaultScatterPlotSeriesSettings();
    series1->xs = x;
    series1->xsLength = 3;
    series1->ys = y1;
    series1->ysLength = 3;
    series1->linearInterpolation = true;
    series1->lineType = L"solid";
    series1->lineTypeLength = wcslen(series1->lineType);
    series1->lineThickness = 2;
    series1->color = CreateRGBColor(1, 0, 0);

    ScatterPlotSeries *series2= GetDefaultScatterPlotSeriesSettings();
    series2->xs = x;
    series2->xsLength = 3;
    series2->ys = y2;
    series2->ysLength = 3;
    series2->linearInterpolation = true;
    series2->lineType = L"solid";
    series2->lineTypeLength = wcslen(series2->lineType);
    series2->lineThickness = 2;
    series2->color = CreateRGBColor(0, 0, 1);

    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->width = 1920;
    settings->height = 1080;
    settings->autoBoundaries = true;
    settings->autoPadding = true;
    settings->title = L"Evolution of time to search as a function of the number of searches";
    settings->titleLength = wcslen(settings->title);
    settings->xLabel = L"Number of searches";
    settings->xLabelLength = wcslen(settings->xLabel);
    settings->yLabel = L"Time (ms)";
    settings->yLabelLength = wcslen(settings->yLabel);
    ScatterPlotSeries *s [] = {series1, series2};
    settings->scatterPlotSeries = s;
    settings->scatterPlotSeriesLength = 2;

    RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
    errorMessage = (StringReference *)malloc(sizeof(StringReference));
    success = DrawScatterPlotFromSettings(canvasReference, settings, errorMessage);

    if(success){
        ByteArray *pngdata = ConvertToPNG(canvasReference->image);
        WriteToFile(pngdata, "plot.png");
        DeleteImage(canvasReference->image);
        printf("Successfully wrote to plot.png\n");
    } else{
        fprintf(stderr, "Error: ");
        for(int i = 0; i < errorMessage->stringLength; i++){
            fprintf(stderr, "%c", errorMessage->string[i]);
        }
        fprintf(stderr, "\n");
    }

    FreeAllocations();

}