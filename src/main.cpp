// Copyright 2022 NNTU-CS
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include "../include/train.h"
int main() {
  std::vector<int> trainLengths;
  for (int n = 10; n <= 200; n += 10) {
    trainLengths.push_back(n);
  }
  std::mt19937 rng(12345);
  std::uniform_int_distribution<int> dist(0, 1);
  std::ofstream csv("result/experiment_results.csv");
  csv << "n,all_off,all_on,random\n";
  for (int n : trainLengths) {
    Train trainOff;
    for (int i = 0; i < n; ++i) trainOff.addCar(false);
    trainOff.getLength();
    int off = trainOff.getOpCount();
    Train trainOn;
    for (int i = 0; i < n; ++i) trainOn.addCar(true);
    trainOn.getLength();
    int on = trainOn.getOpCount();
    Train trainRand;
    for (int i = 0; i < n; ++i) {
      trainRand.addCar(dist(rng) == 1);
    }
    trainRand.getLength();
    int rnd = trainRand.getOpCount();
    csv << n << "," << off << "," << on << "," << rnd << "\n";
    std::cout << n << " done" << std::endl;
  }
  csv.close();
  std::cout << "Results saved to result/experiment_results.csv" << std::endl;
  return 0;
}
