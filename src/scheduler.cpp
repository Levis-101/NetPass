#include <iostream>
#include <thread>
#include <chrono>
#include "../include/firewall.h"

class SessionReaper {
public:
    // This function runs in the background
    void startSession(std::string macAddress, int durationSeconds) {
        // Create a separate worker thread
        std::thread([this, macAddress, durationSeconds]() {
            std::cout << "[TIMER] Access granted for " << durationSeconds << " seconds." << std::endl;
            
            // Wait for the duration of the subscription
            std::this_thread::sleep_for(std::chrono::seconds(durationSeconds));
            
            // Time is up! Revoke access.
            NetFirewall fw;
            fw.revokeAccess(macAddress);
            
            std::cout << "[TIMER] Subscription expired for " << macAddress << std::endl;
        }).detach(); // .detach lets the thread run independently
    }
};