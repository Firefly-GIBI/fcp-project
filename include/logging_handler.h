/**
 * @file logging_handler.h
 * @brief File handling logging in, logging out and submenus available for logged-in users.
 */

#ifndef BANKING_APP_LOGGING_IN_HANDLER_H
#define BANKING_APP_LOGGING_IN_HANDLER_H

#include "accounts.h"
#include "database_manager.h"
#include "choosing_operation.h"
#include "deposit_and_withdraw_handler.h"

/**
 * @brief 8-digit ID of user's account.
 */
inline int logged_in_user_account_id = 0;

/**
 * @brief ID of the logged-in user account in the C++ vector to easily find its database entry and modify it.
 */
inline int logged_in_user_database_id = 0;

/**
 * @brief Owner of the logged-in user account (for example "John Smith").
 */
inline string logged_in_user_account_owner = "Error";

/**
 * @brief Function handles logging in to the user account.
 */
inline void log_in_to_user() {
    string login;
    string password;
    int i = 0;
    bool logging_process = true;

    do {
        cout << "Enter your login: " << endl;
        getline(cin, login);
        cout << "Enter your password: " << endl;
        getline(cin, password);
        for (i = 0; i < users.size(); i++) {
            if (login == users[i].login and password == users[i].password){
                cout << "Successful logging in!" << endl;
                logged_in_user_account_id = users[i].user_id;
                logged_in_user_database_id = i;
                logged_in_user_account_owner = users[i].owner;
                logging_process = false;
            }
        }
        // Ending logging in process when it is successful
        if (!logging_process) {
            break;
        }

        bool invalid_choice = false;
        do {
            cout << "Logging in failed. Try logging in again?" << endl;
            cout << "[1] Yes" << endl;
            cout << "[2] No" << endl;
            switch (choosing_operation()) {
                case 0:
                default:
                    cout << "Invalid choice. Try again." << endl;
                    invalid_choice = true;
                    break;
                case 1:
                    invalid_choice = false;
                    break;
                case 2:
                    return;
            }
        }
        while (invalid_choice);
    }
    while (logging_process);
}

/**
 * @brief Function displays all the user's accounts.
 */
inline void check_my_accounts() {
    if (logged_in_user_account_id) {
        cout << "Your accounts: " << endl;
        int number_of_accounts = users[logged_in_user_database_id].user_accounts_ids.size();
        for (int user_index = 0; user_index < number_of_accounts; user_index++) {
            int account_id = users[logged_in_user_database_id].user_accounts_ids[user_index];
            for (int database_index = 0; database_index < accounts.size(); database_index++) {
                if (accounts[database_index].account_id == account_id) {
                    cout << "[" << user_index + 1 << "]" << endl;
                    cout << "- Account type: " << accounts[database_index].account_type << endl;
                    cout << "- Account balance: " << accounts[database_index].balance_int << "." <<
                        accounts[database_index].balance_float  << endl;
                }
            }
        }
    }
    else {
        cout << "You are not logged in!" << endl;
    }
}

/**
 * @brief Function handles balance management submenu.
 *
 * @param account_database_index ID of the account in the C++ vector to easily find its database entry and use, or
 * modify it.
 */
inline void account_balance_management(const int account_database_index) {
    cout << "What do you want to do?" << endl;
    cout << "[1] Deposit money" << endl;
    cout << "[2] Withdraw money" << endl;
    cout << endl;
    cout << "[9] Exit" << endl;

    switch (choosing_operation()) {
        case 0:
            default:
            cout << "Invalid operation." << endl;
            break;
        case 1:
            deposit(account_database_index);
            update_accounts_database();
            break;
        case 2:
            withdraw(account_database_index);
            update_accounts_database();
            break;
        case 9:
            return;
    }
}

/**
 * @brief Function handles accounts management submenu.
 */
inline void accounts_management() {
    if (logged_in_user_account_id) {
        string chosen_account_number;
        cout << "Your accounts: " << endl << endl;
        for (int user_index = 0; user_index < users[logged_in_user_database_id].user_accounts_ids.size(); user_index++) {
            int account_id = users[logged_in_user_database_id].user_accounts_ids[user_index];
            for (int database_index = 0; database_index < accounts.size(); database_index++) {
                if (accounts[database_index].account_id == account_id) {
                    cout << "[" << user_index + 1 << "]" << endl;
                    cout << "- Account type: " << accounts[database_index].account_type << endl;
                    cout << "- Account balance: " << accounts[database_index].balance_int << "." <<
                        accounts[database_index].balance_float << endl << endl;
                }
            }
        }

        bool invalid_account_choice;

        do {
            cout << "Which account do you want to manage?" << endl;
            cout << "[0] Go back" << endl << endl;
            getline(cin, chosen_account_number);

            invalid_account_choice = false;

            if (chosen_account_number == "0") {
                return;
            }

            for (char character : chosen_account_number) {
                if (!isdigit(character)) {
                    invalid_account_choice = true;
                    break;
                }
            }

            int number_of_accounts = users[logged_in_user_database_id].user_accounts_ids.size();
            if (invalid_account_choice == false and stoi(chosen_account_number) > number_of_accounts) {
                invalid_account_choice = true;
            }

            if (!invalid_account_choice) {
                cout << "-------------------------------------------------------------------" << endl;
                cout << "Your choice is account number [" << chosen_account_number << "]" << endl;
                const int& account_id = users[logged_in_user_database_id].user_accounts_ids[stoi(chosen_account_number) - 1];
                int account_database_index = 0;
                for (int database_index = 0; database_index < accounts.size(); database_index++) {
                    if (accounts[database_index].account_id == account_id) {
                        account_database_index = database_index;
                    }
                }
                cout << "- Account type: " << accounts[account_database_index].account_type << endl;
                cout << "- Account balance: " << accounts[account_database_index].balance_int << "." <<
                    accounts[account_database_index].balance_float << endl << endl;

                bool invalid_operation = true;

                do {
                    cout << "What do you want to manage on your account?" << endl;
                    cout << "[1] Balance management" << endl;
                    cout << endl;
                    cout << "[9] Exit" << endl;
                    switch (choosing_operation()) {
                        case 0:
                        default:
                            cout << "Invalid operation. Try again" << endl;
                            break;
                        case 1:
                            account_balance_management(account_database_index);
                            invalid_operation = false;
                            break;
                        case 9:
                            return;
                    }
                }
                while (invalid_operation);
            }
            else {
                cout << "Invalid choice. Try again." << endl;
            }
        }
            while (invalid_account_choice);
    }
    else {
        cout << "You are not logged in!" << endl;
    }
}

/**
 * @brief Function handles logging out of the logged-in user.
 */
inline void log_out() {
    if (logged_in_user_account_id) {
        logged_in_user_account_id = 0;
        cout << "Successfully logged out!" << endl;
    }
    else {
        cout << "You are not logged in!" << endl;
    }
}

#endif //BANKING_APP_LOGGING_IN_HANDLER_H