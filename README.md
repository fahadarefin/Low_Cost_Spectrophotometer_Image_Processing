Introduction:
This user manual provides instructions for using the Spectrum Analysis code written in C. The code takes a monochrome BMP image file containing spectrum data and generates a standard spectrum graph using Gnuplot. This manual will guide you through the process of downloading and installing the necessary software and running the code successfully.

Software Requirements:
Before running the Spectrum Analysis code, you need to download and install the following software:

a. Gnuplot: Gnuplot is a command-line graphing utility. 
b. Image Conversion Tool: You need a tool to convert your spectrum data into a monochrome BMP image file.

Running the Spectrum Analysis Code:
Follow the steps below to run the Spectrum Analysis code:

a. Convert Spectrum Data to BMP:
Use any image conversion tool to convert your spectrum data into a monochrome BMP image file. Make sure to set the dimensions as 500x10.

b. Download and Compile the Code:
Download the Spectrum Analysis code and paste it on your favorite IDE. Make sure that the .c file and spectrum.bmp file is on the same destination. If not change the path for the spectrum.bmp file.

d. Provide Input:
The program will prompt you to enter the minimum and maximum wavelengths (in nm) for the spectrum analysis. Enter the values as per your spectrum data.

e. Graph Generation:
The code will analyze the BMP image file, calculate the intensities for each wavelength, and generate a standard spectrum graph using Gnuplot. A separate window with the graph will appear.

Viewing the Spectrum Graph:
Once the graph window appears, you can interact with it using Gnuplot's interface. You can zoom in/out, pan, and explore the generated spectrum graph.

Cleaning Up:
After viewing the spectrum graph, you can close the Gnuplot window. The code will automatically free the allocated memory and exit.

Troubleshooting:
If you encounter any issues or errors while running the Spectrum Analysis code, make sure to double-check the following:

Gnuplot is installed correctly, and its executable is added to the system's PATH environment variable.
The BMP image file is correctly converted to monochrome with dimensions 500x10.
The Spectrum Analysis code is compiled successfully without any errors.
If the problem persists, consider seeking assistance from a technical expert or referring to the documentation of the respective software.

Note: It is recommended to have basic knowledge of C programming and familiarity with the command-line interface to ensure a smooth experience with the Spectrum Analysis code.
