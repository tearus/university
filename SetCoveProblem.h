#ifndef UNIVERSITY_SETCOVEPROBLEM_H
#define UNIVERSITY_SETCOVEPROBLEM_H

#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <random>
#include <map>
#include <limits>

// Функция для вычисления пересечения двух множеств
std::vector<int> intersection(const std::vector<int> &set1, const std::vector<int> &set2) {
    std::vector<int> result; // Результат пересечения
    std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(result));
    return result; // Возвращаем результат
}

// Функция для выбора покрывающего множества
std::pair<std::vector<int>, std::vector<std::vector<int>>>
selectCoveringSet(const std::vector<std::vector<int>> &sets, const std::vector<int> &universe) {
    std::vector<int> resultIds; // Индексы выбранных множеств
    std::vector<std::vector<int>> resultSets; // Выбранные множества
    std::vector<int> uncovered = universe; // Список элементов, которые еще не покрыты

    // Цикл, продолжающийся до тех пор, пока не будут покрыты все элементы
    while (!uncovered.empty()) {
        int maxCoverage =  0; // Максимальное количество покрытых элементов
        int minOverlap = std::numeric_limits<int>::max(); // Минимальное перекрытие с уже выбранными множествами
        std::vector<int> bestSet; // Лучшее множество для покрытия
        int bestSetIndex = -1; // Индекс лучшего множества

        // Перебор всех множеств
        for (size_t i =  0; i < sets.size(); ++i) {
            const auto &set = sets[i];
            std::vector<int> covered = intersection(set, uncovered); // Пересечение множества и непокрытых элементов
            if (covered.size() > maxCoverage) {
                maxCoverage = covered.size();
                bestSet = set;
                bestSetIndex = i;
                minOverlap = std::numeric_limits<int>::max();
            }

            int overlap =  0; // Перекрытие с уже выбранными множествами
            for (const auto &existingSet: resultSets) {
                overlap += intersection(set, existingSet).size();
            }
            if (overlap < minOverlap && covered.size() >= maxCoverage) {
                maxCoverage = covered.size();
                bestSet = set;
                bestSetIndex = i;
                minOverlap = overlap;
            }
        }

        // Проверка, не было ли уже выбрано лучшее множество
        bool isAlreadySelected = std::any_of(resultSets.begin(), resultSets.end(),
                                             [&bestSet](const std::vector<int> &existingSet) {
                                                 return existingSet == bestSet;});
        if (isAlreadySelected) {
            continue;
        }

        // Добавление лучшего множества в результат
        resultIds.push_back(bestSetIndex);
        resultSets.push_back(bestSet);
        // Удаление покрытых элементов из списка непокрытых
        uncovered.erase(std::remove_if(uncovered.begin(), uncovered.end(), [&bestSet](int element) {
            return std::find(bestSet.begin(), bestSet.end(), element) != bestSet.end();
        }), uncovered.end());
    }

    return {resultIds, resultSets}; // Возвращаем результат
}



#endif //UNIVERSITY_SETCOVEPROBLEM_H
