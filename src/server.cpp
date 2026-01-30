#include "../include/crow_all.h" 
#include "../include/firewall.h" // Point to the header in include/
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

        // Extracting data from M-Pesa JSON
        // Note: .s() gets string, .d() gets double/number
        string phoneNumber = x["PhoneNumber"].s();
        double amount = x["Amount"].d();
        string macAddress = x["MacAddress"].s(); 

        cout << "\n[PAYMENT] Webhook Received!" << endl;
        cout << "   Phone: " << phoneNumber << " | Amount: " << amount << " KES" << endl;
        cout << "   Target MAC: " << macAddress << endl;

        if (amount >= 10.0) {
            // Trigger the Linux Firewall
            if(firewall.authorizeDevice(macAddress)) {
                return crow::response(200, "{\"ResultCode\": 0, \"ResultDesc\": \"Success\"}");
            }
        } 
        
        return crow::response(200, "{\"ResultCode\": 1, \"ResultDesc\": \"Failed\"}");
    });

    // Run the server on all available network interfaces
    app.port(18080).multithreaded().run();
}