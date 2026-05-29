// Copyright 2022 NNTU-CS
// src/main.cpp
#include "../include/train.h"
#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <cmath>

std::vector<std::pair<int, double>> runExperiment(
    const std::vector<int>& trainLengths,
    const std::string& distributionType,
    bool randomDist = false,
    int randomSeed = 42
) {
    std::vector<std::pair<int, double>> results;
    
    std::mt19937 rng(randomSeed);
    std::uniform_int_distribution<int> dist(0, 1);
    
    for (int n : trainLengths) {
        Train train;
        
        if (distributionType == "all_off") {
            for (int i = 0; i < n; i++) {
                train.addCar(false);
            }
        } 
        else if (distributionType == "all_on") {
            for (int i = 0; i < n; i++) {
                train.addCar(true);
            }
        }
        else if (distributionType == "random") {
            for (int i = 0; i < n; i++) {
                train.addCar(dist(rng) == 1);
            }
        }
        
        train.getLength();
        int operations = train.getOpCount();
        
        results.push_back({n, (double)operations});
        
        std::cout << distributionType << " n=" << n << " ops=" << operations << std::endl;
    }
    
    return results;
}

int main() {
    std::vector<int> trainLengths;
    for (int n = 10; n <= 500; n += 10) {
        trainLengths.push_back(n);
    }
    
    std::cout << "Running experiment..." << std::endl;
    
    auto resultsAllOff = runExperiment(trainLengths, "all_off");
    auto resultsAllOn = runExperiment(trainLengths, "all_on");
    auto resultsRandom = runExperiment(trainLengths, "random", true, 12345);
    
    std::ofstream csv("result/experiment_results.csv");
    csv << "n,all_off,all_on,random\n";
    for (size_t i = 0; i < trainLengths.size(); i++) {
        csv << trainLengths[i] << ","
            << resultsAllOff[i].second << ","
            << resultsAllOn[i].second << ","
            << resultsRandom[i].second << "\n";
    }
    csv.close();
    
    std::cout << "\nResults saved to result/experiment_results.csv" << std::endl;
    std::cout << "Use Excel, Google Sheets, or Python to create plot.png" << std::endl;
    
    return 0;
}
