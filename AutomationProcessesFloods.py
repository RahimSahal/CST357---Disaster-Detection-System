import json

sensor_data = parameter[1]
max_index = len(parameter[1])
latest_data = sensor_data[max_index-1]

latest_sensor_data = latest_data["Ultrasonic Sensor"]  # Retrieve the raw sensor data
latest_sensor_value = float(latest_sensor_data)  # Convert to float

threshold = 10  # Replace with your average value

if latest_sensor_value < threshold:
    msgbody = '<p>The current water level is ' + latest_sensor_data + 'cm, which is above the threshold. Flooding might occur as the reading exceeds ' + str(threshold) + ' cm.</p><br>'
    output[1] = "Warning: Potential Flood Risk"
    output[2] = msgbody
    output[3] = 1
else:
    output[1] = ""
    output[2] = ""
    output[3] = ""
