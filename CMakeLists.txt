cmake_minimum_required(VERSION 4.0)
project(banking_app)

set(CMAKE_CXX_STANDARD 20)

add_executable(banking_app main.cpp
        include/accounts.h
        include/database_manager.h
        include/logging_handler.h
        include/creating_accounts_handler.h
        include/choosing_operation.h
        include/deposit_and_withdraw_handler.h
)


target_include_directories(banking_app PRIVATE include/)