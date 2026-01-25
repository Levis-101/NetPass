#include <iostream>
#include <string>
#include "firewall.cpp"   // In a real project, we'd use headers, but this works for now
#include "scheduler.cpp"

int main() {
    NetFirewall firewall;
    SessionReaper reaper;

    std::cout << "========================================" << std::endl;
    std::cout << "   NetPass++ Wi-Fi Gateway Active       " << std::endl;
    std::cout << "========================================" << std::endl;

    // 1. Simulate a user device detected by the router
    std::string userMAC = "44:65:7D:D2:11:AB";
    std::cout << "\n[EVENT] New device detected: " << userMAC << std::endl;

    // 2. Simulate a "Payment Success" from M-Pesa or Stripe
    std::cout << "[PAYMENT] Received payment for 10-second 'Trial' plan." << std::endl;

    // 3. Authorize the device in the firewall
    if (firewall.authorizeDevice(userMAC)) {
        
        // 4. Start the background timer (The Reaper)
        // This will wait 10 seconds and then run revokeAccess()
        reaper.startSession(userMAC, 10);
        
        std::cout << "[SYSTEM] User is now online. Monitoring session..." << std::endl;
    }

    // Keep the main program running so the background thread has time to finish
    std::cout << "\n[DEBUG] Main program staying alive for the timer..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(15));

    std::cout << "\n[SYSTEM] Simulation complete. Shutting down." << std::endl;
    return 0;
}