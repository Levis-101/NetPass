# NetPass++: C++ Subscription-Based Wi-Fi Gateway

![Language](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Linux-lightgrey.svg)
![Status](https://img.shields.io/badge/Status-Active-green.svg)

**NetPass++** is a high-performance system utility designed to monetize Wi-Fi access. It uses C++ to interact directly with the Linux networking stack to manage user sessions, handle payments, and control internet access via MAC address filtering.

---

## 🛠 Features
- **Captive Portal:** Redirects unauthorized users to a professional login/payment page.
- **MAC Filtering:** Uses `iptables` system calls to whitelist devices in real-time.
- **Subscription Logic:** Supports Daily, Weekly, and Monthly access tiers.
- **Payment Integration:** Communicates with Stripe/M-Pesa APIs using `libcurl`.
- **Session Reaper:** A background thread that automatically disconnects users once their time expires.

---

## ⚙️ Technical Stack
- **Core Language:** C++17 (System-level programming)
- **Web Server:** [Crow](https://github.com/CrowCpp/Crow) (A Fast C++ Framework inspired by Flask)
- **Networking:** Linux `iptables` and Socket Programming.
- **Database:** SQLite (C/C++ API) for user data and logs.
- **API Calls:** `libcurl` for secure payment processing.

---

## 📐 System Architecture


The system intercepts unauthenticated traffic and forces a DNS redirect to a local Crow server. Upon payment verification via a webhook, the `FirewallManager` class executes an `iptables` command to allow the specific MAC address for the purchased duration.

---

## 🚀 Build Instructions
You will need a C++ compiler and `cmake` installed.

```bash
# Clone the repository
git clone [https://github.com/yourusername/NetPass-CPP.git](https://github.com/yourusername/NetPass-CPP.git)
cd NetPass-CPP

# Create build directory
mkdir build && cd build

# Compile
cmake ..
make

# Run (Requires sudo for firewall access)
sudo ./NetPass

🛠️ System Architecture & How it Works
NetPass++ is built on a high-performance C++17 stack designed for low-latency network management.

1. The Gateway Listener (Crow API)
The system runs a multi-threaded Crow web server that exposes a REST endpoint (/mpesa-callback). This listener waits for a JSON payload from the M-Pesa Daraja API. When a payment is confirmed:

It validates the transaction amount.

It extracts the user's MAC address from the metadata.

2. The Firewall Controller (Linux Iptables)
Once payment is verified, the NetFirewall class takes over. It uses System Calls to manipulate the Linux Kernel's packet-filtering rules:

Granting Access: sudo iptables -I FORWARD -m mac --mac-source [MAC] -j ACCEPT

Revoking Access: sudo iptables -D FORWARD -m mac --mac-source [MAC] -j ACCEPT

3. The Session Reaper (Concurrency)
To handle timed subscriptions (e.g., 1 hour of internet), the system spawns an asynchronous thread using <thread>. This "Reaper" sleeps for the duration of the purchased plan and then automatically triggers a firewall rule deletion, ensuring the user is disconnected exactly when their time expires.

4. Persistent Storage (SQLite/CSV)
Every transaction is logged into a persistent storage layer. This ensures that even if the router restarts, we have a record of:

Phone Number (for customer support)

Amount Paid (for business analytics)

Timestamp (for session recovery)

## 💰 Supported Subscription Plans
The system automatically detects the payment amount from M-Pesa and grants access based on the following tiers:

| Amount (KES) | Duration | Description |
| :--- | :--- | :--- |
| **15** | 3 Hours | Student / Short-term pass |
| **30** | 6 Hours | Half-day access |
| **50** | 24 Hours | Full Day Unlimited |
| **100** | 3 Days | Weekend / Mini-pass |
| **150** | 7 Days | Weekly Subscription |
| **400** | 30 Days | Monthly Premium |

## 🛠 Recent Updates
- **Multi-Tier Logic:** Implemented a descending conditional check to ensure users are granted the correct time-slice for their payment.
- **Enhanced Logging:** Transactions are now logged to `transactions.csv` with timestamps and MAC addresses for auditing.
- **Session Reaper Integration:** Integrated a background thread that automatically revokes `iptables` rules upon session expiry.