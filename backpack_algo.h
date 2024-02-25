#include <iostream>
#include <vector>
#ifndef UNIVERSITY_BACKPACK_ALGO_H
#define UNIVERSITY_BACKPACK_ALGO_H
int knapsack(int capacity, int item_count, int *weights, int *costs, bool *selected) {
    std::vector<std::vector<int>> backpack(item_count + 1, std::vector<int>(capacity + 1, 0));

    for (int curr_item = 0; curr_item <= item_count; curr_item++) {
        for (int item_weight = 0; item_weight <= capacity; item_weight++) {
            if (curr_item == 0 || item_weight == 0)
                backpack[curr_item][item_weight] = 0;
            else if (weights[curr_item - 1] <= item_weight)
                backpack[curr_item][item_weight] = std::max(costs[curr_item - 1] + backpack[curr_item - 1][item_weight - weights[curr_item - 1]], backpack[curr_item - 1][item_weight]);
            else
                backpack[curr_item][item_weight] = backpack[curr_item - 1][item_weight];
        }
    }


    int curr_weight = capacity;
    for (int i = item_count; i > 0 && curr_weight > 0; i--) {
        if (backpack[i][curr_weight] != backpack[i - 1][curr_weight]) {
            selected[i - 1] = true;
            curr_weight -= weights[i - 1];
        }
    }

    return backpack[item_count][capacity];
}

#endif //UNIVERSITY_BACKPACK_ALGO_H
