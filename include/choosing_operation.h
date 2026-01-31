/**
 * @file choosing_operation.h
 * @brief File containing choosing_operation() function.
 */

#ifndef BANKING_APP_CHOOSING_OPERATION_H
#define BANKING_APP_CHOOSING_OPERATION_H

#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Function takes user input to convert it into choice for menus functions.
 */
inline int choosing_operation() {
    cout << endl;

    string declared_operation;
    int actual_operation = 0;

    getline(std::cin, declared_operation);

    if (declared_operation == "y") {
        declared_operation = "1";
    }
    else if (declared_operation == "n") {
        declared_operation = "2";
    }

    if (isdigit(declared_operation[0])){
        actual_operation = declared_operation[0];
    }
    else{
        // 48 is ASCII offset
        actual_operation = 48;
    }

    cout << "-------------------------------------------------------------------" << endl;
    // 48 is ASCII offset
    actual_operation -= 48;
    return actual_operation;
}

#endif //BANKING_APP_CHOOSING_OPERATION_H