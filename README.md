# 🚀 NetPass: Subscription-Based Wi-Fi Captive Portal

![Python](https://img.shields.io/badge/python-3.10+-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Status](https://img.shields.io/badge/status-In--Development-orange.svg)

**NetPass** is an automated Wi-Fi access management system that combines a captive portal, automated MAC-address filtering, and subscription-based payment processing. Designed for small businesses, cafes, or community hotspots.

## 🛠 Features
- **Captive Portal:** Automatic redirection of unauthenticated users to a login/payment page.
- **Subscription Tiers:** Daily, Weekly, and Monthly access plans.
- **Automated MAC Filtering:** Dynamically updates router firewall rules (`iptables`) based on payment status.
- **Payment Integration:** Supports Stripe/PayPal/M-Pesa for automated billing.
- **Dashboard:** Admin view to track active connections and revenue.

## 📐 System Architecture


The system operates by intercepting DNS/HTTP requests from unauthorized MAC addresses and routing them to a local Flask server. Once the payment API returns a "Success" webhook, the backend executes a script to whitelist the device's MAC address for the duration of the subscription.

## 💻 Tech Stack
- **Backend:** Python (Flask/FastAPI)
- **Database:** SQLite/PostgreSQL (User records & MAC timestamps)
- **Networking:** Hostapd, Dnsmasq, Iptables (on Linux/OpenWrt)
- **Payments:** Stripe API / M-Pesa Daraja API
- **Frontend:** Bootstrap 5 (Responsive Login Portal)

## 🚀 Quick Start
1. **Clone the repo:**
   ```bash
   git clone [https://github.com/yourusername/netpass-wifi.git](https://github.com/yourusername/netpass-wifi.git)
