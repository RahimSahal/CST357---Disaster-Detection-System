import json

sensor_data = parameter[1]
max_index = len(parameter[1])
latest_data = sensor_data[max_index-1]

latest_sensor_data = latest_data["Soil moisture"]  # Retrieve the raw sensor data
latest_sensor_value = float(latest_sensor_data)  # Convert to float

threshold = 10  # Replace with your average value

if latest_sensor_value < threshold:
    msgbody = '<p>The current soil moisture is ' + latest_sensor_data + '%, which is below the threshold. The reading is less than ' + str(threshold) + '%. This indicates that drought might happen. Please take necessary precautions to mitigate water scarcity.</p><br>'
    output[1] = "Warning: Potential Drought Risk!"
    output[2] = msgbody
    output[3] = 1
else:
    output[1] = ""
    output[2] = ""
    output[3] = ""
