import json

sensor_data = parameter[1]

max_index = len(parameter[1])

latest_data = sensor_data[max_index-1]

latest_sensor_data = latest_data["Temperature"]  # Retrieve the raw sensor data
latest_sensor_value = float(latest_sensor_data)  # Convert to float

threshold = 30  # Replace with your average value

if latest_sensor_value > threshold:
    msgbody = '<p>The current temperature ' + latest_sensor_data + '°C is above threshold, the reading is more than ' + str(threshold) + '°C' + '.</p><br>'
    output[1] = "Warning: High Temperature Reading!"
    output[2] = msgbody
    output[3] = 1
else:
    output[1] = ""
    output[2] = ""
    output[3] = ""
