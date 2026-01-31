/**
 * @file main.cpp
 * @brief File containing main menu loop.
 */

#include "include/database_manager.h"
#include "include/logging_handler.h"
#include "include/creating_accounts_handler.h"
#include "include/choosing_operation.h"

using namespace std;

/**
 * @brief Function containing database initialization and main menu loop serving as a linker to other submenus and
 * functions.
 */
int main() {
    database_initialization();

    bool banking_app_running = true;

    do {
        cout << "-------------------------------------------------------------------" << endl;
        cout << "What do you want to do?" << endl;
        cout << "[1] Log in to my user account" << endl;
        cout << "[2] Check my accounts" << endl;
        cout << "[3] Create a user account" << endl;
        cout << "[4] Create an account" << endl;
        cout << "[5] Accounts management" << endl;
        cout << "[6] Log out" << endl;
        cout << endl;
        cout << "[9] Exit" << endl;

        switch (choosing_operation()) {
        case 0:
            default:
            cout << "Invalid choice!" << endl;
            continue;
        case 1:
            log_in_to_user();
            continue;
        case 2:
            check_my_accounts();
            continue;
        case 3:
            create_user();
            continue;
        case 4:
            create_account();
            continue;
        case 5:
            accounts_management();
            continue;
        case 6:
            log_out();
            continue;
        case 9:
            banking_app_running = false;
        }
    }
    while (banking_app_running);

cout << "Thanks for using our app! :)" << endl;
cout << "-------------------------------------------------------------------" << endl;
}