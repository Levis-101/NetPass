#include "../include/database.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>

DatabaseManager::DatabaseManager() {
    // In a real app, you'd open a connection to "netpass.db" here
    std::cout << "[DB] Connected to NetPass Storage Engine." << std::endl;
}

bool DatabaseManager::logPayment(std::string phone, std::string mac, double amount) {
    // We will save this to a simple text file (CSV) as a database simulation
    std::ofstream dbFile;
    dbFile.open("transactions.csv", std::ios_base::app); // Append mode
    
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    
    dbFile << std::ctime(&now) << "," << phone << "," << mac << "," << amount << "\n";
    dbFile.close();

    std::cout << "[DB] Transaction saved for: " << phone << std::endl;
    return true;
}