#include "../include/firewall.h"
#include <iostream>
#include <cstdlib>

bool NetFirewall::authorizeDevice(const std::string& macAddress) {
    // This command inserts a rule at the top of the FORWARD chain
    std::string command = "sudo iptables -I FORWARD -m mac --mac-source " + macAddress + " -j ACCEPT";
    std::cout << "[FIREWALL] Authorizing: " << macAddress << std::endl;
    return (system(command.c_str()) == 0);
}

bool NetFirewall::revokeAccess(const std::string& macAddress) {
    // This removes the specific rule for that MAC
    std::string command = "sudo iptables -D FORWARD -m mac --mac-source " + macAddress + " -j ACCEPT";
    std::cout << "[FIREWALL] Revoking: " << macAddress << std::endl;
    return (system(command.c_str()) == 0);
}
