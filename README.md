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
