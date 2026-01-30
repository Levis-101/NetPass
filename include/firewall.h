#ifndef FIREWALL_H
#define FIREWALL_H

#include <string>
#include <vector>

/**
 * @class NetFirewall
 * @brief Manages Linux iptables rules to control Wi-Fi access via MAC addresses.
 */
class NetFirewall {
public:
    // Adds a MAC address to the "Allowed" list
    bool authorizeDevice(const std::string& macAddress);

    // Removes a MAC address from the "Allowed" list (Session Expiry)
    bool revokeAccess(const std::string& macAddress);

    // Check if a MAC is currently whitelisted (Utility)
    bool isDeviceAuthorized(const std::string& macAddress);

private:
    // Helper to execute system shell commands securely
    int executeCommand(const std::string& command);
};

#endif
