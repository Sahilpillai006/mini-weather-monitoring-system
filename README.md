# Mini Weather Monitoring Station

A compact Arduino/ESP based mini weather station designed to monitor real-time environmental conditions using a DHT11 sensor and OLED display. This project includes the complete source code, circuit wiring, and a custom 3D printable enclosure designed to neatly house all components.

The system displays real-time:
- Temperature
- Humidity
- Current weather condition status

The enclosure is designed with external airflow access for accurate sensor readings while keeping the electronics protected inside the housing.

---

## Features

- Real-time temperature and humidity monitoring
- OLED live display output
- Compact custom 3D printable enclosure
- Beginner-friendly wiring and setup
- Lightweight and low power design
- Expandable web server support for remote monitoring
- Modular design for future IoT integration

---

## Components Used

- Arduino Nano / ESP8266
- DHT11 Temperature and Humidity Sensor
- OLED Display (I2C)
- Jumper Wires
- Breadboard / PCB
- USB Power Source
- Custom 3D Printed Enclosure

---

## Wiring

### OLED Display (I2C)

| OLED Pin | Arduino Nano |
|----------|---------------|
| VCC | 3.3V / 5V |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

### DHT11 Sensor

| DHT11 Pin | Arduino Nano |
|-----------|---------------|
| VCC | 3.3V / 5V |
| GND | GND |
| DATA | Digital Pin |

---

## 3D Enclosure

The project includes a custom designed 3D printable enclosure made to fit:
- OLED display
- DHT11 sensor
- Arduino board

The sensor section is exposed for better airflow and accurate environmental readings while keeping the electronics protected inside the enclosure.

---

## Files Included

- Arduino source code
- Circuit wiring reference
- STL / 3D model files
- Project images

---

## Future Improvements

- Web dashboard for live monitoring
- Remote access over WiFi
- Historical weather data logging
- Battery backup support
- OTA firmware updates
- ESP32 based cloud integration
- Mobile friendly monitoring interface

---

## Preview

(Add project images here)

---

## License

This project is open-source and available under the MIT License.
