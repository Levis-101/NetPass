#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>

class DatabaseManager {
public:
    DatabaseManager();
    // Saves a payment record to the database
    bool logPayment(std::string phone, std::string mac, double amount);
    
    // Checks if a MAC address has an active session (for reboots)
    bool isSessionActive(std::string mac);
};

#endif