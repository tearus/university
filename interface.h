
#ifndef UNIVERSITY_INTERFACE_H
#define UNIVERSITY_INTERFACE_H

#include <iostream>
#include <vector>
#include "backpack_algo.h"
#include <random>
#include <algorithm>
#include <pareto.h>
#include <SetCoveProblem.h>
#include <fstream>

void backpack_test() {
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

void plotWithGnuplot(std::vector<std::vector<int>> best_cars, std::vector<std::vector<int>> cars) {
    std::string plot = "plot";
    std::ofstream scriptFile(plot);
    if (!scriptFile) {
        std::cerr << "Не удалось создать файл скрипта для gnuplot." << std::endl;
        return;
    }
    scriptFile << "set term wxt" << std::endl
               << "set xrange[100:500]\n"
               << "set yrange[10:50]\n"
               << "set zrange[10000:60000]\n"
               << "set xlabel \"cкорость\"" << std::endl
               << "set ylabel \"Расход топлива\"" << std::endl
               << "set zlabel \"Цена\" " << std::endl
               << "set title \"Фронт Парето\"\n"
               << "$cars << EOD\n";
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 3; ++j) {
            scriptFile << cars[i][j] << " ";
        }
        scriptFile << std::endl;
    }
    scriptFile << "EOD\n";
    scriptFile << "$best_cars << EOD\n";
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 3; ++j) {
            scriptFile << best_cars[i][j] << " ";
        }
        scriptFile << std::endl;
    }
    scriptFile << "EOD\n"
               << "set multiplot\n"
               << "splot $cars with points\n"
               << "replot$best_cars with lines\n"
               << "unset multiplot \n"
               << "pause -1" << std::endl;
    scriptFile.close();
    std::string command = "gnuplot " + plot;
    system(command.c_str());
}

void pareto_test() {
    std::vector<std::vector<int>> cars(100, std::vector<int>(3));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> speedDist(100, 500);
    std::uniform_int_distribution<> fuelDist(10, 50);
    std::uniform_int_distribution<> priceDist(10000, 50000);

    for (auto &car: cars) {
        car[0] = speedDist(gen);
        car[1] = fuelDist(gen);
        car[2] = priceDist(gen);
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
    for (size_t i = 0; i < weights.size(); ++i) {
        weightIndexPairs.emplace_back(weights[i], i);
    }
    std::sort(weightIndexPairs.begin(), weightIndexPairs.end(), [](const auto &a, const auto &b) {
        return a.first > b.first; // Сортируем по убыванию "веса"
    });
    std::vector<std::vector<int>> best_cars(0, std::vector<int>(3));
    for (int i = 0; i < 10 && i < weightIndexPairs.size(); ++i) {
        best_cars.push_back(cars[weightIndexPairs[i].second]);
        std::cout << "Automobile: ";
        for (int num: cars[weightIndexPairs[i].second]) {
            std::cout << num << " ";
        }
        std::cout << "\nWeight: " << weightIndexPairs[i].first << std::endl;
    }
    plotWithGnuplot(best_cars, cars);
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
