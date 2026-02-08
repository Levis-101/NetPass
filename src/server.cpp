#include "../include/crow_all.h" 
#include "../include/firewall.h"
#include "../include/database.h"  // Added
#include "../include/scheduler.h" // Added
#include <iostream>

using namespace std;

int main() {
    crow::SimpleApp app;
    NetFirewall firewall;

    cout << "==========================================" << endl;
    cout << ">>> NetPass M-Pesa Listener: Port 18080" << endl;
    cout << "==========================================" << endl;

    // Route: M-Pesa Webhook Endpoint
    CROW_ROUTE(app, "/mpesa-callback").methods(crow::HTTPMethod::POST)
    ([&firewall](const crow::request& req) {
        
        auto x = crow::json::load(req.body);
        
        if (!x) {
            return crow::response(400, "Invalid JSON");
        }

        // Extracting data
        string phoneNumber = x["PhoneNumber"].s();
        double amount = x["Amount"].d();
        string macAddress = x["MacAddress"].s(); 

        cout << "\n[PAYMENT] Webhook Received!" << endl;
        cout << "   Phone: " << phoneNumber << " | Amount: " << amount << " KES" << endl;

        int durationSeconds = 0;

        // Determine duration based on amount
        if (amount >= 400)      durationSeconds = 2592000; // 30 Days
        else if (amount >= 150) durationSeconds = 604800;  // 7 Days
        else if (amount >= 100) durationSeconds = 259200;  // 3 Days
        else if (amount >= 50)  durationSeconds = 86400;   // 24 Hours
        else if (amount >= 30)  durationSeconds = 21600;   // 6 Hours
        else if (amount >= 15)  durationSeconds = 10800;   // 3 Hours
        else if (amount >= 10)  durationSeconds = 3600;    // 1 Hour

        if (durationSeconds > 0) {
            DatabaseManager db;
            SessionReaper reaper;
            
            db.logPayment(phoneNumber, macAddress, amount);
            
            if(firewall.authorizeDevice(macAddress)) {
                reaper.startSession(macAddress, durationSeconds);
                
                cout << "[SUCCESS] Granted access for " << durationSeconds << "s to " << macAddress << endl;
                return crow::response(200, "Success");
            }
            return crow::response(500, "Firewall Error");
        } else {
            cout << "[REJECTED] Amount " << amount << " is too low." << endl;
            return crow::response(400, "Insufficient Amount");
        }
    }); // <--- THIS WAS MISSING: Closes the route lambda and function

    // Run the server
    app.port(18080).multithreaded().run();
}