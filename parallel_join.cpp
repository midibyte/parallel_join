/* 
    Logan Kelly 
    Parallel Join

    example tables from wikipedia

    //tables
    std::map<std::string, int> employee_table;
    std::map<int, std::string> department_table;

    // setup tables
    employee_table["Rafferty"] = 31;
    employee_table["Jones"] = 33;
    employee_table["Heisenberg"] = 33;
    employee_table["Robinson"] = 34;
    employee_table["Smith"] = 34;
    employee_table["Williams"] = -1;

    department_table[31] = "Sales";
    department_table[33] = "Engineering";
    department_table[34] = "Clerical";
    department_table[35] = "Marketing";
 */

#include <thread>       // threads
#include <string>       
#include <random>       // for shuffle and rand function
#include <iomanip>
#include <cstdlib>
#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

#include "helper.hpp"

//for srand
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    using namespace std;

    std::cout << "argc == " << argc << '\n';

    if (argc != 4){
        printf("Inputs: table 1 size, table 2 size, number of threads\n");
        return EXIT_FAILURE;
    }

    size_t threadCount, tableASize, tableBSize;

    threadCount = atoi(argv[3]);
    tableASize = atoi(argv[1]);
    tableBSize = atoi(argv[2]);

    printf("input: tableASize, tableBSize, threadCount: %zu, %zu, %zu\n", tableASize, tableBSize, threadCount);


    vector<int> employee_table_vec;
    vector<int> department_table_vec;
    vector<int> matches;
    vector<int> matches_threaded;

    /* 
        create the vectors with random elements 
        shuffle the key vector
     */
    srand(time(NULL));   // init for rand(), should only be called once.
    fill_vector_with_random_values(employee_table_vec, tableASize, 0, tableBSize);
    fill_vector_with_unique_increasing_values(department_table_vec, tableBSize);

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(department_table_vec.begin(), department_table_vec.end(), g);
    // display(list);

    // shuffle(department_table_vec.begin(), department_table_vec.end(), rand());


    ssTimer timer;
    timer.startTimer();
    join_vectors_multithreaded(employee_table_vec, department_table_vec, matches_threaded, threadCount);
    timer.endTimer();

    timer.printTimeElapsed();

    timer.clearTimer();
    timer.startTimer();
    join_vectors(employee_table_vec, department_table_vec, matches);
    timer.endTimer();

    timer.printTimeElapsed();

    // print first few values
    print_vector(employee_table_vec, "employee_table_vec", 10);
    print_vector(department_table_vec, "department_table_vec", 10);
    print_vector(matches, "matches", 10);
    print_vector(matches_threaded, "matches_threaded", 10);

    // check results
    

    return 0;
}