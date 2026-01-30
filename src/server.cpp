#include "../include/crow_all.h" // You need the library file here!
#include "../include/firewall.h"
#include <iostream.h>

int main() {
    crow::SimpleApp app;
    NetFirewall firewall;

    std::cout << ">>> NetPass Payment Listener Started on Port 18080" << std::endl;

    // Route: This is where M-Pesa sends the payment confirmation
    // URL: http://your-server-ip:18080/mpesa-callback
    CROW_ROUTE(app, "/mpesa-callback").methods(crow::HTTPMethod::POST)
    ([&firewall](const crow::request& req) {
        
        // 1. Parse the incoming JSON from M-Pesa
        auto x = crow::json::load(req.body);
        
        if (!x) {
            return crow::response(400, "Invalid JSON");
        }

        std::cout << "[MPESA] Webhook Received!" << std::endl;

        // 2. Extract Data (Simulated M-Pesa Payload Structure)
        // In reality, M-Pesa JSON is nested, but we'll keep it simple
        std::string phoneNumber = x["PhoneNumber"].s();
        double amount = x["Amount"].d();
        std::string macAddress = x["MacAddress"].s(); // You'd likely pass this in the Reference

        std::cout << "   User: " << phoneNumber << std::endl;
        std::cout << "   Paid: " << amount << " KES" << std::endl;

        // 3. Logic: If they paid enough, open the internet
        if (amount >= 10.0) {
            firewall.authorizeDevice(macAddress);
            return crow::response(200, "{\"ResultCode\": 0, \"ResultDesc\": \"Service Granted\"}");
        } else {
            return crow::response(200, "{\"ResultCode\": 1, \"ResultDesc\": \"Insufficient Funds\"}");
        }
    });

    // Start the server
    app.port(18080).multithreaded().run();
}