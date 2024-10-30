import serial
import time
import numpy as np
import csv
from sklearn.linear_model import LinearRegression
import matplotlib.pyplot as plt

ser = serial.Serial('/dev/cu.usbmodem11101', 9600)

data = []

try:
    print("Starting to read data. Press CTRL+C to exit.")
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()
            print(line)

            parsed_line = line.split(";")
            if len(parsed_line) == 4:
                pwm1 = int(parsed_line[0].split(":")[1].strip())
                pwm2 = int(parsed_line[1].split(":")[1].strip())
                impulses1 = int(parsed_line[2].split(":")[1].strip())
                impulses2 = int(parsed_line[3].split(":")[1].strip())
                data.append([pwm1, pwm2, impulses1, impulses2])

except KeyboardInterrupt:
    print("\nStopped.")
    ser.close()

if data:
    csv_filename = "collected_data.csv"
    with open(csv_filename, mode="w", newline="") as csv_file:
        writer = csv.writer(csv_file)
        writer.writerow(["PWM1", "PWM2", "Impulses1", "Impulses2"])
        writer.writerows(data)
    print(f"Saved data in file: {csv_filename}")

    data_array = np.array(data)
    pwm1_values = data_array[:, 0].reshape(-1, 1)
    impulses1_values = data_array[:, 2]
    pwm2_values = data_array[:, 1].reshape(-1, 1)
    impulses2_values = data_array[:, 3]

    model1 = LinearRegression().fit(pwm1_values, impulses1_values)
    model2 = LinearRegression().fit(pwm2_values, impulses2_values)

    a1, b1 = model1.coef_[0], model1.intercept_
    a2, b2 = model2.coef_[0], model2.intercept_

    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 6))

    ax1.scatter(pwm1_values, impulses1_values, color="blue", label="Data (Engine 1)")
    ax1.plot(pwm1_values, model1.predict(pwm1_values), color="red",
             label=f"Regression: Impuls = {a1:.2f} * PWM + {b1:.2f}")
    ax1.set_xlabel("PWM1")
    ax1.set_ylabel("Impulses per second")
    ax1.set_title("Engine 2: impulses to PWM relation")
    ax1.legend()

    ax2.scatter(pwm2_values, impulses2_values, color="green", label="Data (Engine 2)")
    ax2.plot(pwm2_values, model2.predict(pwm2_values), color="red",
             label=f"Regresion: Impuls = {a2:.2f} * PWM + {b2:.2f}")
    ax2.set_xlabel("PWM2")
    ax2.set_ylabel("Impulses per second")
    ax2.set_title("Engine 2: impulses to PWM relation")
    ax2.legend()

    plt.tight_layout()
    plt.show()

    print("\nModel for Engine 1:")
    print(f"Impulses1 = {a1:.2f} * PWM1 + {b1:.2f}")
    print("\nModel for Motor 2:")
    print(f"Impulses2 = {a2:.2f} * PWM2 + {b2:.2f}")
else:
    print("No data was collected.")
