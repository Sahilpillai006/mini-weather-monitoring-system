# Mini Weather Monitoring Station

A compact ESP8266 based mini weather station designed to monitor real-time environmental conditions using a DHT11 sensor and OLED display. This project includes complete source code, circuit wiring, and a custom 3D printable enclosure designed to neatly house all components.

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
- ESP8266 web server support for remote monitoring
- Expandable IoT ready architecture

---

## Components Used

- ESP8266 NodeMCU
- DHT11 Temperature and Humidity Sensor
- OLED Display (I2C)
- Jumper Wires
- Breadboard / PCB
- USB Power Source
- Custom 3D Printed Enclosure

---

## Wiring

### OLED Display (I2C)

| OLED Pin | ESP8266 |
|----------|----------|
| VCC | 3.3V |
| GND | GND |
| SDA | D2 |
| SCL | D1 |

### DHT11 Sensor

| DHT11 Pin | ESP8266 |
|-----------|----------|
| VCC | 3.3V |
| GND | GND |
| DATA | D4 |
---

<img width="1176" height="953" alt="weather_station_schem" src="https://github.com/user-attachments/assets/b997c102-a9eb-479c-9583-a96f1622099e" />

---

<img width="1950" height="1033" alt="weather_station_bb" src="https://github.com/user-attachments/assets/9123ef59-1458-4a9e-baae-fba6520d0e1d" />

---

## 3D Enclosure

The project includes a custom designed 3D printable enclosure made to fit:
- ESP8266 NodeMCU
- OLED display
- DHT11 sensor

The sensor section is exposed for better airflow and accurate environmental readings while keeping the electronics protected inside the enclosure.

---

## Files Included

- ESP8266 source code
- Circuit wiring reference
- STL / 3D model files
- Project images

---

## Future Improvements

- Live web dashboard
- Remote access over WiFi
- Historical weather data logging
- Battery backup support
- OTA firmware updates
- Cloud based monitoring
- Mobile friendly interface

---
## Author

**Sahil B Pillai**  
Engineer | Robotics & AI Enthusiast

---

## License

This project is open-source and available under the MIT License.
