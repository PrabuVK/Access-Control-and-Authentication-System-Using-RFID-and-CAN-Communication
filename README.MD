# 🛡️ BattleGuard: Multi-Node Embedded Access Control

## Advanced Military-Grade Authentication via RFID and CAN Bus

---

## 📌 1. Project Overview

**BattleGuard** is a distributed, multi-node embedded security system designed to manage and monitor access to restricted environments. 

Built around **LPC2129 ARM7 microcontrollers**, the system utilizes a combination of **RFID authentication, CAN bus communication, GSM alerts, and automated servo control** to create a seamless and secure entry gateway. 

**Key Implementations:**
* Embedded C & ARM7 Architecture (LPC2129)
* CAN & UART Communication Protocols
* RFID Interfacing (EM-18)
* PWM-based Servo Motor Control
* GSM SMS Notifications
* LCD Display & GPIO Alert Systems (LED/Buzzer)

---

## 📝 2. Abstract

In highly sensitive and restricted zones, manual security checks are both time-consuming and prone to human error. **BattleGuard** solves this by automating the authentication process through a distributed embedded network.

When a user presents an RFID tag, an **EM-18 reader** scans and transmits the ID via **UART** to the primary microcontroller (ECU 1). This node verifies the ID against a secure database of authorized personnel. 

The verification result is then broadcasted across a **CAN bus** to secondary nodes. If authorized, the gate-control node (ECU 2) triggers a **servo motor via PWM** to open the gate, while the monitoring node (ECU 3) displays a success message on a **20×4 LCD**. If unauthorized, the gate remains locked, local alarms (LED/Buzzer) are triggered, and a **GSM module** dispatches an SMS alert to security administrators.

---

## 🎯 3. Core Objectives

* **Automated Authentication:** Verify personnel using RFID technology.
* **Distributed Processing:** Utilize multiple LPC2129 nodes communicating reliably over a CAN network.
* **Actuation & Control:** Drive a servo motor via PWM for automated physical gate management.
* **Real-time Monitoring:** Provide immediate visual feedback via a 20x4 LCD interface.
* **Intrusion Alerting:** Trigger local (Buzzer/LED) and remote (GSM SMS) alarms for unauthorized access attempts.

---

## 🏗️ 4. System Architecture

```text
 [ RFID TAG ] 
      │
      ▼
 [ EM-18 READER ] ──(UART)──▶ [ ECU 1: LPC2129 ]
                              • RFID Verification
                              • GSM SMS Alerts
                              • CAN Transmission
                                      │
                                  [CAN BUS]
                                      │
             ┌────────────────────────┴────────────────────────┐
             ▼                                                 ▼
    [ ECU 2: LPC2129 ]                                [ ECU 3: LPC2129 ]
    • CAN Reception                                   • CAN Reception
    • PWM Generation                                  • 20x4 LCD Control
    • Servo/Gate Control                              • LED & Buzzer Alerts



🔧 5. Hardware & Software Setup
🛠️ Hardware Requirements
Microcontroller: LPC2129 ARM7TDMI-S (Built-in CAN, PWM, UART)

Authentication: EM-18 RFID Reader & Compatible Tags

Networking: CAN Transceivers & Bus lines

Actuation: Servo Motor

Alerts & Display: 20×4 LCD, Active Buzzer, LEDs, GSM Module

Misc: Power Supply, Jumper Wires, ARM7 Development Boards

💻 Software & Tools
Programming Language: Embedded C

IDE: Keil µVision

Debugging: CAN debugging tools / Logic Analyzers



⚙️ 6. Step-by-Step Working Principle
Tag Scanning: An individual places their RFID card near the EM-18 module.

Data Transmission: The 12-character RFID string is sent to ECU 1 via UART.

ID Verification: ECU 1 compares the scanned ID against internally programmed authorized tags.

Network Broadcast: ECU 1 formats the result (e.g., 0x01 for Valid, 0x02 for Invalid) and broadcasts it over the CAN bus.

Gate Actuation (ECU 2):

If Valid: ECU 2 generates a PWM signal to rotate the servo 90°, opening the gate. It closes automatically after a programmed delay.

If Invalid: The servo holds at 0° (gate remains closed).

Status Display (ECU 3):

If Valid: LCD outputs ACCESS GRANTED.

If Invalid: LCD outputs ACCESS DENIED.

Security Alerts: On an invalid scan, ECU 3 activates the buzzer and warning LEDs. Simultaneously, ECU 1 triggers the GSM module to send a security breach SMS.

System Reset: The network clears the current state and returns to idle, awaiting the next RFID scan.




✅ 7. System Advantages
High Reliability: CAN bus architecture ensures robust, error-free communication between subsystems.

Modularity: The distributed multi-node setup makes it easy to add more features (like a camera node) without overloading a single processor.

Instantaneous Response: Automated verification significantly reduces wait times at checkpoints.

Multi-Layered Security: Combines physical barriers, local alarms, and remote text notifications.




🎯 8. Practical Applications
🪖 Military bases and defense facilities

🏢 Government buildings and restricted laboratories

🏭 Industrial warehouses and secure storage areas

🚇 Transport infrastructure (railways, metro staff zones)

🚗 Automated parking and residential access control



👤 Author
PrabuVK


📄 License
This project was developed by Prabu for educational and academic purposes.