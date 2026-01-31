/**
 * @file deposit_and_withdraw_handler.h
 * @brief File handling money deposition to and withdrawal from the account.
 */

#ifndef BANKING_APP_WITHDRAW_AND_DEPOSIT_HANDLER_H
#define BANKING_APP_WITHDRAW_AND_DEPOSIT_HANDLER_H

/**
 * @brief Function handles deposition of money to the account.
 *
 * @param account_database_index ID of the account in the C++ vector to easily find its database entry and use, or
 * modify it.
 */
inline void deposit(const int account_database_index) {
    string deposit_amount_int_part;
    string deposit_amount_float_part;

    bool invalid_deposit_amount;

    do {
        string declared_deposit_amount = "0";
        deposit_amount_int_part = "0";
        deposit_amount_float_part = "0";

        const int current_balance_int = accounts[account_database_index].balance_int;
        const int current_balance_float = accounts[account_database_index].balance_float;

        const float current_amount = stof(to_string(current_balance_int) + "." + to_string(current_balance_float));

        cout << "How much do you want to deposit?" << endl;
        cout << "Current amount: " << current_amount << endl << endl;

        invalid_deposit_amount = false;
        int number_of_floating_points = 0;
        
        getline(cin, declared_deposit_amount);

        int character_index = 0;
        int floating_point_index = 100;

        for (const char character : declared_deposit_amount) {
            // Program checks for floating points and allows for only 1
            if (character == '.' or character == ',') {
                number_of_floating_points ++;

                if (number_of_floating_points <= 1) {
                    floating_point_index = character_index;
                    declared_deposit_amount[character_index] = '.';
                }
                // There's no need for checking rest of the loop if the character is a floating point,
                // so we skip it.
                character_index++;
                continue;
            }

            // Program only checks 2 digits after the floating point
            if (character_index > floating_point_index + 2) {
                break;
            }
            // Program checks for any invalid characters (other than numbers and 1 floating point)
            if (!isdigit(character)) {
                cout << "Invalid character." << endl;
                invalid_deposit_amount = true;
                break;
            }


            // Program checks if the character is still a natural number or already a floating point
            if (character_index > floating_point_index) {
                deposit_amount_float_part += character;
            }
            else {
                deposit_amount_int_part += character;
            }

            character_index++;
        }
    }
    while (invalid_deposit_amount);

    // If user's input was only integer part, assume floating point is just 0.
    if (deposit_amount_float_part.empty()) {
        deposit_amount_float_part = "0";
    }

    cout << "Deposit amount: " << stoi(deposit_amount_int_part) << "." <<
        stoi(deposit_amount_float_part) << endl;

    accounts[account_database_index].balance_int += stoi(deposit_amount_int_part);
    accounts[account_database_index].balance_float += stoi(deposit_amount_float_part);

    if (accounts[account_database_index].balance_float >= 100) {
        accounts[account_database_index].balance_float -= 100;
        accounts[account_database_index].balance_int += 1;
    }

    cout << "Current amount is: " << accounts[account_database_index].balance_int << "." <<
        accounts[account_database_index].balance_float << endl;
}

/**
 * @brief Function handles withdrawal of money from the account.
 *
 * @param account_database_index ID of the account in the C++ vector to easily find its database entry and modify it.
 */
inline void withdraw(const int account_database_index) {
    string withdraw_amount_int_part;
    string withdraw_amount_float_part;

    bool invalid_withdraw_amount;

    do {
        string declared_withdraw_amount = "0";
        withdraw_amount_int_part = "0";
        withdraw_amount_float_part = "0";

        const int current_balance_int = accounts[account_database_index].balance_int;
        const int current_balance_float = accounts[account_database_index].balance_float;

        const float current_amount = stof(to_string(current_balance_int) + "." + to_string(current_balance_float));


        if (current_amount <= 0) {
            cout << "You have no money to withdraw." << endl;
            break;
        }

        cout << "How much do you want to withdraw?" << endl;
        cout << "Current amount: " << current_amount << endl << endl;

        invalid_withdraw_amount = false;
        int number_of_floating_points = 0;

        getline(cin, declared_withdraw_amount);

        int character_index = 0;
        int floating_point_index = 100;

        for (const char character : declared_withdraw_amount) {
            // Program checks for floating points and allows for only 1
            if (character == '.' or character == ',') {
                number_of_floating_points ++;

                if (number_of_floating_points <= 1) {
                    floating_point_index = character_index;
                    declared_withdraw_amount[character_index] = '.';
                }
                // There's no need for checking rest of the loop if the character is a floating point,
                // so we skip it.
                character_index++;
                continue;
            }

            // Program only checks 2 digits after the floating point
            if (character_index > floating_point_index + 2) {
                break;
            }
            // Program checks for any invalid characters (other than numbers and 1 floating point)
            if (!isdigit(character)) {
                cout << "Invalid character." << endl;
                invalid_withdraw_amount = true;
                break;
            }


            // Program checks if the character is still a natural number or already a floating point
            if (character_index > floating_point_index) {
                withdraw_amount_float_part += character;
            }
            else {
                withdraw_amount_int_part += character;
            }

            character_index++;
        }
        if (stof(withdraw_amount_int_part + "." + withdraw_amount_float_part) > current_amount) {
            cout << "There isn't enough money on account for such amount" << endl;
            invalid_withdraw_amount = true;
        }
    }
    while (invalid_withdraw_amount);

    // If user's input was only integer part, assume floating point is just 0.
    if (withdraw_amount_float_part.empty()) {
        withdraw_amount_float_part = "0";
    }

    cout << "Withdraw amount: " << stoi(withdraw_amount_int_part) << "." <<
        stoi(withdraw_amount_float_part) << endl;

    accounts[account_database_index].balance_int -= stoi(withdraw_amount_int_part);
    accounts[account_database_index].balance_float -= stoi(withdraw_amount_float_part);

    if (accounts[account_database_index].balance_float < 0) {
        accounts[account_database_index].balance_float += 100;
        accounts[account_database_index].balance_int -= 1;
    }

    cout << "Current amount is: " << accounts[account_database_index].balance_int << "." <<
        accounts[account_database_index].balance_float << endl;
}

#endif //BANKING_APP_WITHDRAW_AND_DEPOSIT_HANDLER_H