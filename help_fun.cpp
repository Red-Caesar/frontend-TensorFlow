#include "help_fun.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

int calculate_median(std::vector<int32_t> &v)
{
    size_t n = v.size() / 2;
    nth_element(v.begin(), v.begin()+n, v.end());
    return v[n];
}

float calculate_std(std::vector<int32_t> &data, int size){
    float sum = 0.0;
    float std = 0.0;

    for(int i = 0; i < size; ++i) {
        sum += data[i];
    }
    float mean = sum / size;
    for(int i = 0; i < size; ++i) {
        std += pow(data[i] - mean, 2);
    }
    return sqrt(std / size);
}

int metrics(const int16_t* samples, int size, char name[]){
    std::vector<int32_t> data(size);
    for (int i = 0; i < size; ++i) {
        data[i] = (int32_t)*samples++;
    }
    int32_t max = *max_element(data.begin(), data.end());
    int32_t min = *min_element(data.begin(), data.end());
    int32_t median = calculate_median(data);
    float std = calculate_std(data, size);
    std::cout << name << '\n';
    std::cout << "max: " << max << ' ' <<  "min: " << min << ' ' << "median: "
    << median << ' ' << "std: " << std << '\n';
    return 0;
}