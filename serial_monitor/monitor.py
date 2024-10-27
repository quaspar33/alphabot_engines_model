import serial
import time
import numpy as np
import csv
from sklearn.linear_model import LinearRegression

ser = serial.Serial('/dev/ttyUSB0', 9600)

data = []

try:
    print("Rozpoczynam odczyt danych. Wciśnij Ctrl+C, aby zakończyć.")
    while True:
        if ser.in_waiting > 0:

            line = ser.readline().decode('utf-8').strip()
            print(line)

            parsed_line = line.split(";")
            if len(parsed_line) == 8:
                pwm1 = int(parsed_line[1])
                pwm2 = int(parsed_line[3])
                impulses1 = int(parsed_line[5])
                impulses2 = int(parsed_line[7])
                data.append([pwm1, pwm2, impulses1, impulses2])

except KeyboardInterrupt:
    print("\nZakończono odczyt.")
    ser.close()

csv_filename = "collected_data.csv"
with open(csv_filename, mode="w", newline="") as csv_file:
    writer = csv.writer(csv_file)
    writer.writerow(["PWM1", "PWM2", "Impulses1", "Impulses2"])
    writer.writerows(data)
print(f"Zapisano dane do pliku {csv_filename}")

data_array = np.array(data)
pwm1_values = data_array[:, 0].reshape(-1, 1)
impulses1_values = data_array[:, 2]
pwm2_values = data_array[:, 1].reshape(-1, 1)
impulses2_values = data_array[:, 3]

model1 = LinearRegression().fit(pwm1_values, impulses1_values)
model2 = LinearRegression().fit(pwm2_values, impulses2_values)

a1, b1 = model1.coef_[0], model1.intercept_
a2, b2 = model2.coef_[0], model2.intercept_

print("\nModel dla Motor 1:")
print(f"Impulses1 = {a1:.2f} * PWM1 + {b1:.2f}")
print("\nModel dla Motor 2:")
print(f"Impulses2 = {a2:.2f} * PWM2 + {b2:.2f}")
