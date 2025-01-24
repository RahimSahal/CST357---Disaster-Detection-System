import json

sensor_data = parameter[1]
max_index = len(parameter[1])
latest_data = sensor_data[max_index-1]

latest_sensor_data = latest_data["Humidity"]  # Retrieve the raw sensor data
latest_sensor_value = float(latest_sensor_data)  # Convert to float

threshold = 80  # Replace with your average value

if latest_sensor_value > threshold:
    msgbody = '<p>The current humidity ' + f'{latest_sensor_value:.2f}' + '% is above threshold, the reading is more than ' + str(threshold) + '%' + '.</p><br>'
    output[1] = "Abnormal Humidity Reading Detected!"
    output[2] = msgbody
    output[3] = 1
else:
    output[1] = ""
    output[2] = ""
    output[3] = ""
