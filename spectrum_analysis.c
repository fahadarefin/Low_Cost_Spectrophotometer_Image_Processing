#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#define IMAGE_WIDTH 500
#define IMAGE_HEIGHT 10
#define MAX_COLOR_INTENSITY 255

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} Pixel;

int main() {
    FILE* imageFile = fopen("spectrum.bmp", "rb");  // If the image is in other location Replace "spectrum.bmp" with the actual image file path
    if (imageFile == NULL) {
        printf("Failed to open the image file.\n");
        return 1;
    }

    // Skip the BMP file header (14 bytes)
    fseek(imageFile, 14, SEEK_SET);

    // Read the BMP image pixel data
    Pixel image[IMAGE_HEIGHT][IMAGE_WIDTH];
    for (int row = 0; row < IMAGE_HEIGHT; row++) {
        fread(&image[row][0], sizeof(Pixel), IMAGE_WIDTH, imageFile);
    }

    fclose(imageFile);

    // User input for minimum and maximum wavelengths
    int minWavelength, maxWavelength;
    printf("Enter the minimum wavelength (in nm): ");
    if (scanf("%d", &minWavelength) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    printf("Enter the maximum wavelength (in nm): ");
    if (scanf("%d", &maxWavelength) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    // Calculate wavelength step size
    double wavelengthStep = (double)(maxWavelength - minWavelength) / (IMAGE_WIDTH - 1);

    // Calculate intensity for each pixel column
    int intensities[IMAGE_WIDTH];
    for (int col = 0; col < IMAGE_WIDTH; col++) {
        int maxIntensity = 0;

        // Find the maximum intensity in the column
        for (int row = 0; row < IMAGE_HEIGHT; row++) {
            // Get the RGB values of the pixel
            uint8_t red = image[row][col].red;
            uint8_t green = image[row][col].green;
            uint8_t blue = image[row][col].blue;

            // Check if the pixel is white (assuming intensity is proportional to the height of the white pixel)
            if (red == MAX_COLOR_INTENSITY && green == MAX_COLOR_INTENSITY && blue == MAX_COLOR_INTENSITY) {
                int height = IMAGE_HEIGHT - row - 1;  // Calculate the height from the bottom (reversed due to image coordinate system)
                int intensity = (height * MAX_COLOR_INTENSITY) / (IMAGE_HEIGHT - 1);  // Calculate intensity as a fraction of the maximum height
                if (intensity > maxIntensity) {
                    maxIntensity = intensity;
                }
            }
        }

        intensities[col] = maxIntensity;
    }

    // Plot the graph using Gnuplot
    FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe == NULL) {
        printf("Failed to open Gnuplot pipe.\n");
        return 1;
    }

    // Set Gnuplot settings
    fprintf(gnuplotPipe, "set term wxt\n");  // Set the terminal type as a window
    fprintf(gnuplotPipe, "set xlabel 'Wavelength (nm)'\n");  // Set the x-axis label
    fprintf(gnuplotPipe, "set ylabel 'Intensity'\n");  // Set the y-axis label
    fprintf(gnuplotPipe, "set title 'Spectrum Analysis'\n");  // Set the graph title
    fprintf(gnuplotPipe, "plot '-' with lines title 'Intensity'\n");  // Begin plotting with lines and a title

    // Plot the intensity values
    for (int col = 0; col < IMAGE_WIDTH; col++) {
        double wavelength = minWavelength + col * wavelengthStep;
        fprintf(gnuplotPipe, "%f %d\n", wavelength, intensities[col]);  // Print wavelength and intensity values
    }
    fprintf(gnuplotPipe, "e\n");  // End of data marker for Gnuplot

    fflush(gnuplotPipe);  // Flush the pipe to ensure all data is written
    pclose(gnuplotPipe);  // Close the Gnuplot pipe

    return 0;
