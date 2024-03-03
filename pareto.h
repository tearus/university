#ifndef LAB2_1_PARETO_H
#define LAB2_1_PARETO_H

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

double calculateWeight(const std::vector<int> &car, const std::vector<double> &coefficients) {
    double weight = 0;
    for (size_t i = 0; i < car.size(); ++i) {
        if (i == 2) {
            weight -= car[i] * coefficients[i] * 0.01;
        }
        if (i == 1) {
            weight -= car[i] * coefficients[i] * 10;
        } else if(i==0){
            weight += car[i] * coefficients[i];
        }
    }
    return weight;
}

void print_cars(const std::vector<std::vector<int>> &cars) {
    std::cout << "Automobiles:\n";
    for (const auto &car: cars) {
        std::cout << "Speed: " << car[0] << ", Fuel consumption: " << car[1] << ", Price: " << car[2] << std::endl;
    }
}


#endif //LAB2_1_PARETO_H
