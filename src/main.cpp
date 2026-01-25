#include "../include/firewall.h"
#include <iostream>
#include <cstdlib> // Required for std::system

bool NetFirewall::authorizeDevice(const std::string& macAddress) {
    // Command: Insert (-I) a rule into the FORWARD chain to ACCEPT traffic from this MAC
    std::string command = "sudo iptables -I FORWARD -m mac --mac-source " + macAddress + " -j ACCEPT";
    
    std::cout << "[LOG] Attempting to authorize: " << macAddress << std::endl;
    
    if (runSystemCommand(command) == 0) {
        std::cout << "[SUCCESS] Device " << macAddress << " is now whitelisted." << std::endl;
        return true;
    }
    return false;
}

bool NetFirewall::revokeAccess(const std::string& macAddress) {
    // Command: Delete (-D) the specific rule for this MAC address
    std::string command = "sudo iptables -D FORWARD -m mac --mac-source " + macAddress + " -j ACCEPT";
    
    std::cout << "[LOG] Revoking access for: " << macAddress << std::endl;
    return (runSystemCommand(command) == 0);
}

int NetFirewall::runSystemCommand(const std::string& command) {
    // Converts std::string to a C-style string and executes it in the shell
    return std::system(command.c_str());
}
