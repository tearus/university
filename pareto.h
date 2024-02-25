#ifndef LAB2_1_PARETO_H
#define LAB2_1_PARETO_H
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

// Функция для вычисления "веса" автомобиля на основе заданных коэффициентов
double calculateWeight(const std::vector<int> &car, const std::vector<double> &coefficients) {
    double weight =   0;
    for (size_t i =   0; i < car.size(); ++i) {
        weight += car[i] * coefficients[i]; // Умножаем каждую характеристику на соответствующий коэффициент и суммируем
    }
    return weight;
}

// Функция для вывода информации об автомобилях
void print_cars(const std::vector<std::vector<int>>& cars) {
    std::cout << "Automobiles:\n";
    for (const auto& car : cars) {
        std::cout << "Speed: " << car[0] << ", Fuel consumption: " << car[1] << ", Price: " << car[2] << std::endl;
    }
}



#endif //LAB2_1_PARETO_H
