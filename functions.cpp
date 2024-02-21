#include "model.h"
#include "functions.h"
#include<iostream>
#include<vector>

void addData(std::vector<std::string>& database, const std::string dataList[], int length){
    for(int i = 0; i<length; i++){
        database.push_back(dataList[i]);
    }
}

double roundData(double num) {
    double fraction = num - std::floor(num);
    if (fraction > 0.5) {
        return std::ceil(num);
    } else {
        return std::floor(num);
    }
}

