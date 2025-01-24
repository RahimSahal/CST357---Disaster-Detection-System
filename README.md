# IoT-Based  Disaster Detection System

This project implements an IoT-based system designed to monitor and manage natural disasters, including floods, landslides, and droughts. The system collects real-time environmental data using sensors 
and provides local alerts through LEDs and a buzzer while integrating with the V-One IoT cloud platform for data visualization and monitoring.

## Features
- Monitors three types of natural disasters: Floods, Landslides, and Droughts.
- Provides real-time alerts with visual (LED), audible (buzzer) indicators and email notifications.
- Integrates with the V-One IoT platform for cloud-based data processing, storage, and visualization.
- Ensures proactive disaster management aligned with SDG 13: Climate Action.

---

## Hardware Components
1. Maker Feather MCU  
   - Serves as the central controller for data collection, processing, and communication with the cloud platform.

2. Sensors
   - **Ultrasonic Sensor:** Monitors water levels for flood detection.  
   - **Soil Moisture Sensor:** Detects soil moisture levels to monitor landslide and drought risks.  
   - **DHT11 Sensor:** Measures temperature and humidity to provide additional data for drought monitoring.

3. Actuators  
   - LEDs: Visual indicators for risk levels:
     - Green: Normal.
     - Yellow: Moderate risk.
     - Red: Critical condition.  
   - Buzzer: Provides an audible warning in critical situations.

---

## Cloud Integration
- V-One IoT Platform
  - Facilitates real-time data visualization through dashboards.
  - Analyze the data like calculating average, maximum and minimum value.
  - Stores and processes data received from the Maker Feather MCU.
  - Do predictions by implementing machine learning.
  - Enables remote monitoring and notifications.

---

## **System Workflow**
1. Sensors collect real-time environmental data.
2. The Maker Feather MCU processes the data and determines risk levels based on predefined thresholds.
3. LEDs and the buzzer provide local alerts.
4. Processed data is sent to the V-One IoT platform for cloud-based visualization and monitoring.

