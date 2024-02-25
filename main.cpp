#include <iostream>
#include "backpack_algo.h"
#include "interface.h"
int main() {
    int task_num;
    std::cout<<"Enter task\n1-backpack\n2-pareto\n3-setcover\n";
    std::cin >>task_num;
    switch (task_num) {
        case 1:
            backpack_test();
            break;
        case 2:
            pareto_test();
            break;
        case 3:
            setcover_test();
            break;
    }
    return 0;
}