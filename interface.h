
#ifndef UNIVERSITY_INTERFACE_H
#define UNIVERSITY_INTERFACE_H
#include <iostream>
#include <vector>
#include "backpack_algo.h"
#include <random>
#include <algorithm>
#include <pareto.h>
#include <SetCoveProblem.h>
void backpack_test(){
    int item_count, capacity;
    std::cout << "Enter item count of elements: ";
    std::cin >> item_count;
    std::cout << "\n";

    std::cout << "Enter knapsack capacity: ";
    std::cin >> capacity;
    std::cout << "\n";

    srand(static_cast<unsigned>(time(0)));

    int *weights = new int[item_count];
    int *costs = new int[item_count];
    bool *selected = new bool[item_count];

    for (int i = 0; i < item_count; ++i) {
        weights[i] = 1 + rand() % 100;
        costs[i] = 1 + rand() % 100;
        selected[i] = false;
    }

    std::cout << "Weights: ";
    for (int i = 0; i < item_count; ++i) {
        std::cout << weights[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Prices: ";
    for (int i = 0; i < item_count; ++i) {
        std::cout << costs[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Max Price: " << knapsack(capacity, item_count, weights, costs, selected) << std::endl;


    std::cout << "Selected items: ";
    for (int i = 0; i < item_count; ++i) {
        if (selected[i]) {
            std::cout << "(" << weights[i] << ", " << costs[i] << ") ";
        }
    }
    std::cout << std::endl;

    delete[] weights;
    delete[] costs;
    delete[] selected;
}
void pareto_test() {
    std::vector<std::vector<int>> cars(100, std::vector<int>(3)); // Создаем вектор автомобилей с  100 элементами, каждый из которых представляет собой вектор из трех характеристик
    std::random_device rd; // Генератор случайных чисел
    std::mt19937 gen(rd()); // Мersenne Twister генератор случайных чисел
    std::uniform_int_distribution<> speedDist(100,   200); // Распределение скорости от  100 до  200 км/ч
    std::uniform_int_distribution<> fuelDist(5,   15); // Распределение расхода топлива от  5 до  15 литров на  100 км
    std::uniform_int_distribution<> priceDist(10000,   50000); // Распределение цен от  10000 до  50000 единиц валюты

    for (auto &car: cars) {
        car[0] = speedDist(gen); // Генерируем случайную скорость
        car[1] = fuelDist(gen); // Генерируем случайный расход топлива
        car[2] = priceDist(gen); // Генерируем случайную цену
    }

    std::string tmp;
    std::cout << "View all automobiles?" << std::endl;
    std::cin >> tmp;
    if (tmp == "y")
        print_cars(cars); // Выводим информацию об автомобилях, если пользователь согласился

    std::vector<double> coefficients(3); // Коэффициенты для вычисления "веса" автомобиля
    std::cout << "Enter   3 coefficients: ";
    for (double &coef: coefficients) {
        std::cin >> coef;
    }

    std::vector<double> weights; // Вектор для хранения "весов" автомобилей
    for (const auto &car: cars) {
        weights.push_back(calculateWeight(car, coefficients)); // Вычисляем "вес" каждого автомобиля
    }

    auto maxWeightIter = std::max_element(weights.begin(), weights.end()); // Находим автомобиль с наибольшим "весом"
    int maxWeightIndex = std::distance(weights.begin(), maxWeightIter);
    std::cout << "\nAutomobile with the highest weight: ";
    for (int num: cars[maxWeightIndex]) {
        std::cout << num << " ";
    }
    std::cout << "\nWeight: " << *maxWeightIter << std::endl;

    std::cout << "10 automobiles with close by weight values:\n";
    std::vector<std::pair<double, int>> weightIndexPairs; // Вектор пар, где первый элемент - "вес", а второй - индекс автомобиля
    for (size_t i =   0; i < weights.size(); ++i) {
        weightIndexPairs.emplace_back(weights[i], i);
    }
    std::sort(weightIndexPairs.begin(), weightIndexPairs.end(), [](const auto &a, const auto &b) {
        return a.first > b.first; // Сортируем по убыванию "веса"
    });

    for (int i =   0; i <   10 && i < weightIndexPairs.size(); ++i) {
        std::cout << "Automobile: ";
        for (int num: cars[weightIndexPairs[i].second]) {
            std::cout << num << " ";
        }
        std::cout << "\nWeight: " << weightIndexPairs[i].first << std::endl;
    }
}
void setcover_test() {
    std::vector<std::vector<int>> sets;
    std::vector<int> universe;

    std::cout << "Enter the universe elements (separated by spaces): ";
    int element;
    while (std::cin >> element) {
        universe.push_back(element);
        if (std::cin.get() == '\n') break;
    }

    std::cout << "Enter the sets\n Each set on a new line, elements separated by spaces,\nWrite end for leave :\n";
    std::vector<int> set;
    while (std::cin >> element) {
        set.push_back(element);
        if (std::cin.get() == '\n') {
            sets.push_back(set);
            set.clear();
        }
    }

    auto [coveringSetIds, coveringSets] = selectCoveringSet(sets, universe);

    std::cout << "Covering sets: ";
    for (int setId: coveringSetIds) {
        std::cout << setId + 1 << " ";
    }
    std::cout << std::endl;

    std::map<int, int> numberCounts;
    for (const auto &set: coveringSets) {
        for (int number: set) {
            numberCounts[number]++;
        }
    }

    std::cout << "numbers encountered more than once: ";
    for (const auto &[number, count]: numberCounts) {
        if (count > 1) {
            std::cout << number << " (" << count << " times) ";
        }
    }
    std::cout << std::endl;
}
#endif //UNIVERSITY_INTERFACE_H
