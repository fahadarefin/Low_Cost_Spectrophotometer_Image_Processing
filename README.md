**User Manual: Spectrum Analysis Script**

*Note: This user manual provides detailed instructions on how to use the "Spectrum Analysis" script to analyze and visualize the intensity of a bitmap image representing a spectrum. Please follow these instructions step by step for successful execution.*

**1. Introduction:**

The "Spectrum Analysis" script is designed to analyze a bitmap image that represents a spectrum and visualize the intensity values across different wavelengths. The script takes an input image file in the BMP format and user-defined minimum and maximum wavelengths. It then generates a graph using Gnuplot to display the intensity of the spectrum at different wavelengths.

**2. Prerequisites:**

Before using the script, ensure you have the following components installed on your system:

- C compiler (GCC recommended)
- Gnuplot

**3. Getting Started:**

Follow these steps to get started with the "Spectrum Analysis" script:

**Step 1:** Prepare your input image: Make sure you have a bitmap image file (BMP format) that represents the spectrum. The image should have dimensions of 25000 pixels width and 500 pixels height.

**Step 2:** Download the script: Obtain the "spectrum_analysis.c" script.

**Step 3:** Compile the script: Open a terminal window and navigate to the directory containing the script and the input image. Compile the script using a C compiler. For example:

```
gcc spectrum_analysis.c -o spectrum_analysis -lm
```

**4. Running the Script:**

Run the compiled script by executing the following command:

```
./spectrum_analysis
```

**5. Using the Script:**

Once the script is executed, follow these steps to use it effectively:

**Step 1:** Image Validation: The script will attempt to open the input image ("spectrum.bmp" by default). If the image fails to open or if its dimensions are not 25000x500 pixels, an error message will be displayed, and the script will terminate.

**Step 2:** Input Wavelength Range: You will be prompted to enter the minimum and maximum wavelengths for the spectrum. Enter these values in nanometers (nm). The script will calculate the wavelength step size based on the image width and the provided range.

**Step 3:** Generating the Graph: The script will process the image and calculate the intensity values for each pixel column. It will then generate a graph using Gnuplot to display the intensity values against the corresponding wavelengths.

**6. Gnuplot Graph:**

The generated graph will be displayed using Gnuplot in a separate window. The graph will have the following features:

- X-axis: Represents the wavelength in nanometers.
- Y-axis: Represents the intensity of the spectrum.
- Title: The title of the graph will be set as "Spectrum Analysis."
- Data Plot: The graph will display a line plot of intensity values against wavelengths.

**7. Exiting the Script:**

After the graph is displayed, you can close the Gnuplot window to exit the script. The script will automatically free allocated memory and terminate.

**8. Troubleshooting:**

If you encounter any issues while using the script, ensure the following:

- The input image is in BMP format and has dimensions of 25000x500 pixels.
- The C compiler and Gnuplot are properly installed on your system.
- The provided input for minimum and maximum wavelengths is valid (integer values).

**9. Cleaning Up:**

After using the script, you can delete the compiled executable ("spectrum_analysis") and other temporary files generated during execution.

**10. Additional Notes:**

- The script handles memory allocation and deallocation to prevent memory leaks.
- If you want to use a different input image, replace "spectrum.bmp" in the script with the actual image file path.
- The script uses the "wxt" terminal type for Gnuplot, which opens a separate window to display the graph. You can modify this behavior by editing the corresponding Gnuplot settings in the script.

**11. Conclusion:**

The "Spectrum Analysis" script provides a convenient way to analyze and visualize the intensity of a spectrum represented by a bitmap image. By following the instructions outlined in this user manual, you can effectively use the script to generate and view the intensity graph of the spectrum.
