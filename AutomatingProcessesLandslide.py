import json

sensor_data = parameter[1]
max_index = len(parameter[1])
latest_data = sensor_data[max_index-1]

latest_sensor_data = latest_data["Soil moisture"]  # Retrieve the raw sensor data
latest_sensor_value = float(latest_sensor_data)  # Convert to float

threshold = 80  # Replace with your average value

if latest_sensor_value > threshold:
    msgbody = '<p>Soil moisture is ' + latest_sensor_data + '%, above the threshold of ' + str(threshold) + '%. Landslide risk detected. Please stay alert and take precautions.</p><br>'
    output[1] = "Warning: Potential Landslide Risk!"
    output[2] = msgbody
    output[3] = 1
else:
    output[1] = ""
    output[2] = ""
    output[3] = ""
