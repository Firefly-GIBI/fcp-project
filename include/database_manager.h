/**
 * @file database_manager.h
 * @brief File managing database (initializing, updating and converting between JSON database and C++ vector).
 */

#ifndef BANKING_APP_DATABASE_MANAGER_H
#define BANKING_APP_DATABASE_MANAGER_H

#include <fstream>
#include <iostream>

#include "accounts.h"

#include "json.hpp"

using json = nlohmann::json;

/**
 * @brief Function converts user accounts from the JSON database to the C++ vector.
 *
 * @param user_accounts_database JSON database of user accounts.
 * @param users C++ vector of user accounts.
 */
inline void from_json(const json& user_accounts_database, User& users) {
    users.user_id = user_accounts_database["user_id"];
    users.login = user_accounts_database["login"];
    users.owner = user_accounts_database["owner"];
    users.password = user_accounts_database["password"];
    users.user_accounts_ids = user_accounts_database["user_accounts_ids"].get<vector<int>>();
}

/**
 * @brief Function converts user accounts from the C++ vector to the JSON database.
 *
 * @param user_accounts_database JSON database of user accounts.
 * @param user Each single user account converted one by one to the C++ vector.
 */
inline void to_json(json& user_accounts_database, const User& user) {
    user_accounts_database["user_id"] = user.user_id;
    user_accounts_database["login"] = user.login;
    user_accounts_database["owner"] = user.owner;
    user_accounts_database["password"] = user.password;
    user_accounts_database["user_accounts_ids"] = user.user_accounts_ids;
}

/**
 * @brief Function converts accounts from the JSON database to the C++ vector.
 *
 * @param accounts_database JSON database of accounts.
 * @param accounts C++ vector of accounts.
 */
inline void from_json(const json& accounts_database, Account& accounts) {
    accounts.account_id = accounts_database["account_id"];
    accounts.account_type_id = accounts_database["account_type_id"];
    accounts.account_type = accounts_database["account_type"];
    accounts.balance_int = accounts_database["balance_int"];
    accounts.balance_float = accounts_database["balance_float"];
    accounts.owner = accounts_database["owner"];
    accounts.owner_id = accounts_database["owner_id"];
    accounts.pin_code = accounts_database["pin_code"];
}

/**
 * @brief Function converts accounts from the C++ vector to the JSON database.
 *
 * @param accounts_database JSON database of accounts.
 * @param account Each single account converted one by one to the C++ vector.
 */
inline void to_json(json& accounts_database, const Account& account) {
    accounts_database["account_id"] = account.account_id;
    accounts_database["account_type_id"] = account.account_type_id;
    accounts_database["account_type"] = account.account_type;
    accounts_database["balance_int"] = account.balance_int;
    accounts_database["balance_float"] = account.balance_float;
    accounts_database["owner"] = account.owner;
    accounts_database["owner_id"] = account.owner_id;
    accounts_database["pin_code"] = account.pin_code;
}

/**
 * @brief Function updates the accounts JSON database.
 */
inline void update_accounts_database() {
    json accounts_database;
    accounts_database["accounts"] = accounts;
    ofstream output("json_files/accounts.json");
    if (!output) {
        cout << "File not found: accounts.json" << endl;
    }
    output << accounts_database.dump(4) << endl;
}

/**
 * @brief Function updates the user accounts JSON database.
 */
inline void update_user_accounts_database() {
    json user_accounts_database;
    user_accounts_database["user_accounts"] = users;
    ofstream output("json_files/user_accounts.json");
    if (!output) {
        cout << "File not found: user_accounts.json" << endl;
    }
    output << user_accounts_database.dump(4) << endl;
}

/**
 * @brief Function initializes the JSON database.
 */
inline void database_initialization() {
    if (ifstream user_accounts_file("json_files/user_accounts.json"); !user_accounts_file.is_open()){
        cout << "File not found: user_accounts.json" << endl;
    }
    else {
        json user_accounts_database;
        user_accounts_file >> user_accounts_database;
        ::users = user_accounts_database["user_accounts"];
    }

    if (ifstream accounts_file("json_files/accounts.json"); !accounts_file.is_open()) {
        cout << "File not found: accounts.json" << endl;
    }
    else {
        json accounts_database;
        accounts_file >> accounts_database;
        ::accounts = accounts_database["accounts"];
    }
}

#endif //BANKING_APP_DATABASE_MANAGER_H