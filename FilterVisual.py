import numpy as np
import matplotlib.pyplot as plt
import matplotlib
matplotlib.use('TKAgg')
'''
class ExponentialFilter:
    def __init__(self, initial_value, smoothing_factor):
        self.filter_output = initial_value
        self.previous_output = initial_value
        self.smoothing_factor = smoothing_factor

    def update(self, measurement):
        self.filter_output = self.smoothing_factor * measurement + (1 - self.smoothing_factor) * self.previous_output
        self.previous_output = self.filter_output
        return self.filter_output

class BiquadIIRFilter:
    def __init__(self, initial_value):
        self.Input_z1 = initial_value
        self.Input_z2 = initial_value
        self.Output_z1 = initial_value
        self.Output_z2 = initial_value
        self.filter_output = initial_value
        self.aCoff = [0.014401418980573148, 0.028802837961146296, 0.014401418980573148]
        self.bCoff = [-1.6329907391512004, 0.690596415073493]

    def update(self, measurement):
        self.filter_output = (self.aCoff[0] * measurement +
                              self.aCoff[1] * self.Input_z1 +
                              self.aCoff[2] * self.Input_z2) - \
                             (self.bCoff[0] * self.Output_z1 +
                              self.bCoff[1] * self.Output_z2)
        self.Input_z2 = self.Input_z1
        self.Input_z1 = measurement
        self.Output_z2 = self.Output_z1
        self.Output_z1 = self.filter_output
        return self.filter_output

class KalmanFilter:
    def __init__(self, process_variance, measurement_variance, initial_estimate, initial_error_estimate):
        self.process_variance = process_variance # Process variance (Q): how much we trust the process model
        self.measurement_variance = measurement_variance  # Measurement variance (R): how much we trust the measurements
        # Initial estimates
        self.estimate = initial_estimate
        self.error_estimate = initial_error_estimate

    def update(self, measurement):
        # Kalman gain (K)
        kalman_gain = self.error_estimate / (self.error_estimate + self.measurement_variance)
        # Update the estimate with the new measurement
        self.estimate = self.estimate + kalman_gain * (measurement - self.estimate)
        # Update the error estimate
        self.error_estimate = (1 - kalman_gain) * self.error_estimate + abs(self.estimate - measurement) * self.process_variance
        return self.estimate

# Generate noisy temperature data
np.random.seed(42)  # For reproducibility
time = np.linspace(0, 20, 1000)  # Increased time points
true_temperature = 25 + 5 * np.sin(0.5 * time)  # Simulated true temperature
noise = np.random.normal(0, 1, size=time.shape)  # Increased Gaussian noise
noisy_temperature = true_temperature + noise  # Noisy data

# Apply the Exponential filter
ef = ExponentialFilter(initial_value=noisy_temperature[0], smoothing_factor=0.1)
filtered_temperature_exponential = [ef.update(temp) for temp in noisy_temperature]

# Apply the Biquad IIR filter
biq = BiquadIIRFilter(initial_value=noisy_temperature[0])
filtered_temperature_biquad = [biq.update(temp) for temp in noisy_temperature]

# Apply the Kalman filter
kf = KalmanFilter(process_variance=0.01, measurement_variance=1.2, initial_estimate=noisy_temperature[0], initial_error_estimate=0)
filtered_temperature_kalman = [kf.update(temp) for temp in noisy_temperature]

# Plot the results
plt.figure(figsize=(12, 6))
plt.plot(time, noisy_temperature, label="Noisy Temperature", color="orange", alpha=0.7)
plt.plot(time, true_temperature, label="True Temperature", color="green", linestyle="--")
plt.plot(time, filtered_temperature_exponential, label="Filtered Temperature (Exponential)", color="red")
plt.plot(time, filtered_temperature_biquad, label="Filtered Temperature (Biquad IIR)", color="purple")
plt.plot(time, filtered_temperature_kalman, label="Filtered Temperature (Kalman)", color="blue")
plt.xlabel("Time")
plt.ylabel("Temperature")
plt.title("Exponential Filter vs Biquad IIR Filter vs Kalman Filter for Temperature Data")
plt.legend()
plt.grid()
plt.show()
'''


import tkinter as tk
from tkinter import ttk
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

# Classes remain the same as in your original code

class ExponentialFilter:
    def __init__(self, initial_value, smoothing_factor):
        self.filter_output = initial_value
        self.previous_output = initial_value
        self.smoothing_factor = smoothing_factor

    def update(self, measurement):
        self.filter_output = self.smoothing_factor * measurement + (1 - self.smoothing_factor) * self.previous_output
        self.previous_output = self.filter_output
        return self.filter_output

class BiquadIIRFilter:
    def __init__(self, initial_value):
        self.Input_z1 = initial_value
        self.Input_z2 = initial_value
        self.Output_z1 = initial_value
        self.Output_z2 = initial_value
        self.filter_output = initial_value
        self.aCoff = [0.014401418980573148, 0.028802837961146296, 0.014401418980573148]
        self.bCoff = [-1.6329907391512004, 0.690596415073493]

    def update(self, measurement):
        self.filter_output = (self.aCoff[0] * measurement +
                              self.aCoff[1] * self.Input_z1 +
                              self.aCoff[2] * self.Input_z2) - \
                             (self.bCoff[0] * self.Output_z1 +
                              self.bCoff[1] * self.Output_z2)
        self.Input_z2 = self.Input_z1
        self.Input_z1 = measurement
        self.Output_z2 = self.Output_z1
        self.Output_z1 = self.filter_output
        return self.filter_output

class KalmanFilter:
    def __init__(self, process_variance, measurement_variance, initial_estimate, initial_error_estimate):
        self.process_variance = process_variance
        self.measurement_variance = measurement_variance
        self.estimate = initial_estimate
        self.error_estimate = initial_error_estimate

    def update(self, measurement):
        kalman_gain = self.error_estimate / (self.error_estimate + self.measurement_variance)
        self.estimate = self.estimate + kalman_gain * (measurement - self.estimate)
        self.error_estimate = (1 - kalman_gain) * self.error_estimate + abs(self.estimate - measurement) * self.process_variance
        return self.estimate

# Generate noisy temperature data
np.random.seed(42)
time = np.linspace(0, 20, 1000)
true_temperature = 25 + 5 * np.sin(0.5 * time)
noise = np.random.normal(0, 1, size=time.shape)
noisy_temperature = true_temperature + noise

# Create the main tkinter window
root = tk.Tk()
root.title("Filter Parameter Adjustment")

# Create a frame for the controls at the top
controls_frame = tk.Frame(root)
controls_frame.grid(row=0, column=0, columnspan=2, pady=10)

# Create a matplotlib figure and embed it in tkinter
fig, ax = plt.subplots(figsize=(10, 5))
canvas = FigureCanvasTkAgg(fig, master=root)
canvas_widget = canvas.get_tk_widget()
canvas_widget.grid(row=1, column=0, columnspan=2, padx=10, pady=10)  # Position the canvas below the controls

# Function to update the plot
def plot_filtered_results(smoothing_factor, process_variance, measurement_variance, filter_type):
    ax.clear()  # Clear the current axes
    
    # Apply the selected filter
    if filter_type == "Exponential":
        ef = ExponentialFilter(initial_value=noisy_temperature[0], smoothing_factor=smoothing_factor)
        filtered_temperature = [ef.update(temp) for temp in noisy_temperature]
        ax.plot(time, filtered_temperature, label="Filtered Temperature (Exponential)", color="red")
    elif filter_type == "BiquadIIR":
        biq = BiquadIIRFilter(initial_value=noisy_temperature[0])
        filtered_temperature = [biq.update(temp) for temp in noisy_temperature]
        ax.plot(time, filtered_temperature, label="Filtered Temperature (Biquad IIR)", color="purple")
    elif filter_type == "Kalman":
        kf = KalmanFilter(process_variance=process_variance, 
                          measurement_variance=measurement_variance, 
                          initial_estimate=noisy_temperature[0], 
                          initial_error_estimate=0)
        filtered_temperature = [kf.update(temp) for temp in noisy_temperature]
        ax.plot(time, filtered_temperature, label="Filtered Temperature (Kalman)", color="blue")
    elif filter_type == "All":
        ef = ExponentialFilter(initial_value=noisy_temperature[0], smoothing_factor=smoothing_factor)
        filtered_temperature_exponential = [ef.update(temp) for temp in noisy_temperature]

        biq = BiquadIIRFilter(initial_value=noisy_temperature[0])
        filtered_temperature_biquad = [biq.update(temp) for temp in noisy_temperature]

        kf = KalmanFilter(process_variance=process_variance, 
                          measurement_variance=measurement_variance, 
                          initial_estimate=noisy_temperature[0], 
                          initial_error_estimate=0)
        filtered_temperature_kalman = [kf.update(temp) for temp in noisy_temperature]

        ax.plot(time, filtered_temperature_exponential, label="Filtered Temperature (Exponential)", color="red")
        ax.plot(time, filtered_temperature_biquad, label="Filtered Temperature (Biquad IIR)", color="purple")
        ax.plot(time, filtered_temperature_kalman, label="Filtered Temperature (Kalman)", color="blue")

    # Plot the noisy and true temperatures
    ax.plot(time, noisy_temperature, label="Noisy Temperature", color="grey", alpha=0.7)
    ax.plot(time, true_temperature, label="True Temperature", color="green", linestyle="--")
    ax.set_xlabel("Time")
    ax.set_ylabel("Temperature")
    ax.set_title("Filter Comparison for Temperature Data")
    ax.legend()
    ax.grid()

    canvas.draw()  # Refresh the canvas

# Function to handle the update button
def update_plot():
    try:
        smoothing_factor = float(smoothing_factor_entry.get())
        process_variance = float(process_variance_entry.get())
        measurement_variance = float(measurement_variance_entry.get())
        filter_type = filter_type_var.get()
        plot_filtered_results(smoothing_factor, process_variance, measurement_variance, filter_type)
        error_label.config(text="")  # Clear error message
    except ValueError:
        error_label.config(text="Please enter valid numbers")

# Create input fields and labels inside the controls frame
tk.Label(controls_frame, text="Smoothing Factor(ExpFilter):").grid(row=0, column=0, padx=10, pady=3, sticky="e")
smoothing_factor_entry = ttk.Entry(controls_frame)
smoothing_factor_entry.insert(0, "0.1")
smoothing_factor_entry.grid(row=0, column=1, padx=10, pady=5)

tk.Label(controls_frame, text="Process Variance(Kalman):").grid(row=0, column=2, padx=10, pady=3, sticky="e")
process_variance_entry = ttk.Entry(controls_frame)
process_variance_entry.insert(0, "0.01")
process_variance_entry.grid(row=0, column=3, padx=10, pady=5)

tk.Label(controls_frame, text="Measurement Variance(Kalman):").grid(row=0, column=4, padx=10, pady=3, sticky="e")
measurement_variance_entry = ttk.Entry(controls_frame)
measurement_variance_entry.insert(0, "1.2")
measurement_variance_entry.grid(row=0, column=5, padx=10, pady=5)

# Create Update button inside the controls frame
update_button = ttk.Button(controls_frame, text="Update", command=update_plot)
update_button.grid(row=0, column=6, padx=10, pady=5)

# Create an error label
error_label = tk.Label(root, text="", fg="red")
error_label.grid(row=3, column=0, columnspan=2)

# Create a variable to store the selected filter type
filter_type_var = tk.StringVar(value="All")

# Create radio buttons for selecting the filter type
tk.Label(controls_frame, text="Filter Type:").grid(row=1, column=0, padx=10, pady=3, sticky="w")
filters = ["Exponential", "BiquadIIR", "Kalman", "All"]
for index, filter_type in enumerate(filters):
    tk.Radiobutton(controls_frame, text=filter_type, variable=filter_type_var, value=filter_type).grid(row=1, column=index + 1, padx=10, pady=3)
    
# Bind the close event
def on_closing():
    plt.close('all')  # Close all matplotlib figures
    root.destroy()    # Destroy the tkinter root window

root.protocol("WM_DELETE_WINDOW", on_closing)

# Initial plot
plot_filtered_results(smoothing_factor=0.1, process_variance=0.01, measurement_variance=1.2, filter_type="All")

# Run the application
root.mainloop()
