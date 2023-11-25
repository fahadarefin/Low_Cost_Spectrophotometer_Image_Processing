import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import find_peaks
from tkinter import filedialog, Tk


# Function to read data from a text file
def read_data(file_path):
    data = np.loadtxt(file_path, delimiter='\t', skiprows=1, comments=['-', 'nm'])
    wavelengths = data[:, 0]
    intensity = data[:, 1]
    return wavelengths, intensity


# Function to calculate absorbance
def calculate_absorbance(before_intensity, after_intensity):
    before_intensity /= np.max(before_intensity)
    after_intensity /= np.max(after_intensity)

    absorbance = -np.log10(after_intensity / (before_intensity + 1e-10))
    absorbance += (-np.min(absorbance))
    absorbance *= 100

    return absorbance


# Function to apply signal smoothing (simple moving average)
def smooth_signal(data, window_size=5):
    kernel = np.ones(window_size) / window_size
    smoothed_data = np.convolve(data, kernel, mode='same')
    return smoothed_data


# Function to plot the graph with optional features
def plot_spectrum(wavelengths, absorbance, mark_peaks=False, apply_smoothing=False):
    if apply_smoothing:
        absorbance = smooth_signal(absorbance)

    plt.figure(figsize=(10, 6))
    plt.plot(wavelengths, absorbance, label='Absorbance', color='blue')

    if mark_peaks:
        peaks, _ = find_peaks(absorbance, height=0.01)

        if peaks.size > 0:
            max_peak_index = np.argmax(absorbance[peaks])
            max_peak_wavelength = wavelengths[peaks][max_peak_index]
            max_peak_value = absorbance[peaks][max_peak_index]

            plt.plot(max_peak_wavelength, max_peak_value, 'rx', label='Max Peak')
        else:
            print("No peaks found.")

    plt.xlabel('Wavelength (nm)')
    plt.ylabel('Absorbance')
    plt.title('Absorbance Spectrum Before and After Solution')
    plt.legend()

    # Save the plot as a JPG file
    plt.savefig('absorbance_spectrum.jpg', format='jpg', dpi=300)

    # Show the plot
    plt.show()


# Function to ask the user for file locations
def ask_for_file_locations():
    root = Tk()
    root.withdraw()  # Hide the main window
    root.attributes('-topmost', True)  # Bring the window to the front
    file_paths = filedialog.askopenfilenames(title='Select TXT files', filetypes=[('TXT files', '*.txt')])
    root.destroy()  # Close the Tkinter window
    return file_paths


# Main function
def main():
    # Ask the user for file locations
    file_paths = ask_for_file_locations()

    if len(file_paths) < 2:
        print("Please select at least two TXT files.")
        return

    # Read data from before and after files
    before_wavelengths, before_intensity = read_data(file_paths[0])
    after_wavelengths, after_intensity = read_data(file_paths[1])

    # Check if wavelengths match between before and after measurements
    if not np.array_equal(before_wavelengths, after_wavelengths):
        raise ValueError("Wavelengths do not match between before and after measurements")

    # Calculate absorbance
    absorbance = calculate_absorbance(before_intensity, after_intensity)

    # Ask the user for optional features
    mark_peaks = input("Do you want to mark the max peak? (yes/no): ").lower() == 'yes'
    apply_smoothing = input("Do you want to apply signal smoothing? (yes/no): ").lower() == 'yes'

    # Plot the graph with optional features
    plot_spectrum(before_wavelengths, absorbance, mark_peaks, apply_smoothing)


# Run the main function if this script is executed
if __name__ == "__main__":
    main()
