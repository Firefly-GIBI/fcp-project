/**
 * @file accounts.h
 * @brief This file contains "User" and "Account" class, makes vectors from them and tells the code how to display them.
 */

#ifndef BANKING_APP_ACCOUNTS_H
#define BANKING_APP_ACCOUNTS_H

#include <vector>
#include <iostream>

using namespace std;

/**
 * @brief Class for accounts
 *
 * @param account_id ID of account
 * @param account_type_id ID of account type (1 = Personal, 2 = Savings, 3 = Credit card, 4 = Loan).
 * @param account_type Type of account ("Personal", "Savings", "Credit card", "Loan").
 * @param balance_float Stores value after floating point (for example 12 cents).
 * @param balance_int Stores value before floating point (for example 57 dollars).
 * @param owner Owner of the account (for example "John Smith").
 * @param owner_id ID of the account's Owner.
 * @param pin_code Four-digit string storing account's PIN code.
 */

class Account {
public:
    int account_id{};
    int account_type_id{};
    string account_type;
    int balance_float{};
    int balance_int{};
    string owner;
    int owner_id{};
    string pin_code;

    Account() = default;
};

/**
 * @brief Vector storing all the accounts. It downloads them from database, store new ones and thereafter uploads them
 * to the database.
 */

inline vector<Account> accounts;

/**
 * @brief Class for user accounts
 *
 * @param user_id ID of the user
 * @param login Login of the owner
 * @param owner Owner of the user account (for example "John Smith")
 * @param password Password for the user account
 * @param user_accounts_ids IDs of the accounts owned by the user
 */

class User {
public:
    int user_id{};
    string login;
    string owner;
    string password;
    vector<int> user_accounts_ids;

    User() = default;
};

/**
 * @brief Vector storing all the user accounts. It downloads them from database, store new ones and thereafter uploads
 * them to the database.
 */

inline vector<User> users;

/**
 * @brief Instruction for the code how to display the Account vector
 */

inline ostream& operator<<(ostream& os, const Account& account) {
    os << "- Account ID: " << account.account_id << endl;
    os << "- Account type ID: " << account.account_type_id << endl;
    os << "- Account type: " << account.account_type << endl;
    os << "- Account balance: " << account.balance_int << "." << account.balance_float;
    os << "- Account owner: " << account.owner << endl;
    os << "- Account owner ID: " << account.owner_id << endl;
    os << "- Account PIN code: " << account.pin_code << endl << endl;;
    return os;
}
/**
 * @brief Instruction for the code how to display the User vector
 */

inline ostream& operator<<(ostream& os, const User& user) {
    os << "- User ID: " << user.user_id << endl;
    os << "- Login: " << user.login << endl;
    os << "- Owner: " << user.owner << endl;
    os << "- Password: " << user.password << endl;
    os << endl << "- Your bank accounts: " << endl << endl;
    for (int user_index = 0; user_index < user.user_accounts_ids.size(); user_index++) {
        int account_id = user.user_accounts_ids[user_index];
        for (int database_index = 0; database_index < accounts.size(); database_index++) {
            if (accounts[database_index].account_id == account_id){
                cout << "[" << user_index + 1 << "] " << endl;
                cout << "- Account type: " << accounts[database_index].account_type << endl;
                cout << "- Account balance: " << accounts[database_index].balance_int << "." <<
                    accounts[database_index].balance_float << endl;
            }
        }
    }
    return os;
}

#endif //BANKING_APP_ACCOUNTS_H