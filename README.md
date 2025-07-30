# ESP32-Based Real-Time Blind Spot Distance Sensor with MQTT

This project uses an **ESP32 microcontroller** and **ultrasonic sensors** to build a real-time **blind spot detection** system. It reads distances using two HC-SR04 sensors and publishes the data over **MQTT**, allowing other systems (like a Qt dashboard) to monitor nearby objects.

---

## 🚗 Use Case

Designed to simulate a car's blind spot monitoring system, this setup can be integrated into a full dashboard or used in robotics and automation scenarios.

---

## 📡 Hardware Setup

* ESP32 Dev Module
* 2x Ultrasonic sensors (HC-SR04)
* Jumper wires
* Breadboard

**Connections per sensor:**

* `Trig` → GPIO 18 / 21
* `Echo` → GPIO 19 / 22

---

## 🔧 Software Requirements

* Arduino IDE
* `WiFi.h` and `PubSubClient.h` libraries
* MQTT broker (e.g. Mosquitto on your PC or Raspberry Pi)

---

## 📜 MQTT Publishing Format

Topic: `ultrasonic/data`

```
u1:123.4cm
u2:87.6cm
```

---

## 🧠 How It Works

1. ESP32 connects to your Wi-Fi network
2. Reads distances from both sensors
3. Publishes the values every second over MQTT

---

## 🖥️ Related Projects

This ESP32 module is designed to work with the Qt GUI Dashboard:
👉 [qt-blind-spot-dashboard](https://github.com/HossamMekkawy2040/qt-blind-spot-dashboard-/tree/main)

---

## 📁 File Structure

```
ESP32_Code/
├── blind_spot.ino
```

---

## 📝 License

MIT
