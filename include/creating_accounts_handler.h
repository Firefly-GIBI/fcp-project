/**
 * @file creating_accounts_handler.h
 * @brief File handling creation of accounts and user accounts.
 */

#ifndef BANKING_APP_CREATING_ACCOUNTS_HANDLER_H
#define BANKING_APP_CREATING_ACCOUNTS_HANDLER_H

#include <iostream>

#include "accounts.h"
#include "logging_handler.h"
#include "database_manager.h"

/**
 * @brief Functions handles creation of a user account.
 */
inline void create_user() {
    if (!logged_in_user_account_id) {
        User new_user;
        cout << "Enter user account owner: " << endl;
        getline(cin, new_user.owner);
        cout << "Enter user account password: " << endl;
        getline(cin, new_user.password);
        cout << "Enter user account login: " << endl;
        getline(cin, new_user.login);

        new_user.user_id = rand() % 99999999 + 11111111;

        users.push_back(new_user);

        update_user_accounts_database();
    }
    else {
        cout << "Log out first!" << endl;
    }
}

/**
 * @brief Functions handles creation of an account.
 */
inline void create_account() {
    if (logged_in_user_account_id) {
        Account new_account;

        bool invalid_operation = true;
        do {
            cout << "Enter account type: " << endl;
            cout << "[1] - Personal account" << endl;
            cout << "[2] - Savings account" << endl;
            cout << "[3] - Credit card account" << endl;
            cout << "[4] - Loan" << endl;
            switch (choosing_operation()) {
                case 0:
                default:
                    cout << "Invalid operation. Try again." << endl;
                    invalid_operation = true;
                    break;
                case 1:
                    new_account.account_type_id = 1;
                    new_account.account_type = "Personal";
                    invalid_operation = false;
                    break;
                case 2:
                    new_account.account_type_id = 2;
                    new_account.account_type = "Savings";
                    invalid_operation = false;
                    break;
                case 3:
                    new_account.account_type_id = 3;
                    new_account.account_type = "Credit card";
                    invalid_operation = false;
                    break;
                case 4:
                    new_account.account_type_id = 4;
                    new_account.account_type = "Loan";
                    invalid_operation = false;
            }
        }
        while (invalid_operation);

        new_account.owner = logged_in_user_account_owner;

        cout << "Enter account PIN code: " << endl;
        getline(cin, new_account.pin_code);

        new_account.account_id = rand() % 99999999 + 11111111;
        new_account.owner_id = logged_in_user_account_id;
        new_account.balance_int = 0;
        new_account.balance_float = 0;

        accounts.push_back(new_account);
        users[logged_in_user_database_id].user_accounts_ids.push_back(new_account.account_id);

        update_accounts_database();
        update_user_accounts_database();

        cout << "Your account id: " << new_account.account_id << endl;
        cout << "Your account type: " << new_account.account_type << endl;
        cout << "Your account owner: " << new_account.owner << endl;
        cout << "Your account PIN code: " << new_account.pin_code << endl;
    }
    else {
        cout << "You are not logged in!" << endl;
    }
}

#endif //BANKING_APP_CREATING_ACCOUNTS_HANDLER_H