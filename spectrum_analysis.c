#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#define MAX_COLOR_INTENSITY 255

typedef struct {
    uint8_t intensity;
} Pixel;

int main() {
    FILE* imageFile = fopen("spectrum.bmp", "rb");  // Replace "spectrum.bmp" with the actual image file path
    if (imageFile == NULL) {
        printf("Failed to open the image file.\n");
        return 1;
    }

    // Read the BMP file header to get the image dimensions
    uint32_t imageDataOffset;
    uint32_t imageWidth;
    uint32_t imageHeight;
    fseek(imageFile, 10, SEEK_SET);
    fread(&imageDataOffset, sizeof(uint32_t), 1, imageFile);
    fseek(imageFile, 18, SEEK_SET);
    fread(&imageWidth, sizeof(uint32_t), 1, imageFile);
    fread(&imageHeight, sizeof(uint32_t), 1, imageFile);

    // Ensure the image dimensions match the requirements
    if (imageWidth != 25000 || imageHeight != 500) {
        printf("Invalid image dimensions.\n");
        fclose(imageFile);
        return 1;
    }

    // Calculate the number of bytes per row (including padding)
    uint32_t bytesPerRow = (imageWidth / 8 + 3) & ~3;

    // Allocate memory for the image
    Pixel** image = (Pixel**)malloc(imageHeight * sizeof(Pixel*));
    if (image == NULL) {
        printf("Memory allocation failed for image.\n");
        fclose(imageFile);
        return 1;
    }

    for (int row = 0; row < imageHeight; row++) {
        image[row] = (Pixel*)malloc(imageWidth / 8 * sizeof(Pixel));
        if (image[row] == NULL) {
            printf("Memory allocation failed for image row %d.\n", row);
            for (int i = 0; i < row; i++) {
                free(image[i]);
            }
            free(image);
            fclose(imageFile);
            return 1;
        }
        fseek(imageFile, imageDataOffset + (imageHeight - 1 - row) * bytesPerRow, SEEK_SET);
        fread(image[row], sizeof(Pixel), imageWidth / 8, imageFile);
    }

    fclose(imageFile);

    // Take user input for minimum and maximum wavelengths
    int minWavelength, maxWavelength;
    printf("Enter the minimum wavelength (in nm): ");
    if (scanf("%d", &minWavelength) != 1) {
        printf("Invalid input.\n");
        for (int row = 0; row < imageHeight; row++) {
            free(image[row]);
        }
        free(image);
        return 1;
    }

    printf("Enter the maximum wavelength (in nm): ");
    if (scanf("%d", &maxWavelength) != 1) {
        printf("Invalid input.\n");
        for (int row = 0; row < imageHeight; row++) {
            free(image[row]);
        }
        free(image);
        return 1;
    }

    // Calculate wavelength step size
    double wavelengthStep = (double)(maxWavelength - minWavelength) / (imageWidth - 1);

    // Calculate intensity for each pixel column
    int* intensities = (int*)calloc(imageWidth, sizeof(int));
    if (intensities == NULL) {
        printf("Memory allocation failed for intensities.\n");
        for (int row = 0; row < imageHeight; row++) {
            free(image[row]);
        }
        free(image);
        return 1;
    }

    for (int col = 0; col < imageWidth; col++) {
        int intensity = 0;

        for (int row = 0; row < imageHeight; row++) {
            uint8_t byte = image[row][col / 8].intensity;
            uint8_t bitMask = 1 << (7 - (col % 8));
            if ((byte & bitMask) != 0) {
                intensity++;
            }
        }

        intensities[col] = intensity;
    }

    // Plot the graph using Gnuplot
    FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe == NULL) {
        printf("Failed to open Gnuplot pipe.\n");
        free(intensities);
        for (int row = 0; row < imageHeight; row++) {
            free(image[row]);
        }
        free(image);
        return 1;
    }

    // Set Gnuplot settings
    fprintf(gnuplotPipe, "set term wxt\n");  // Set the terminal type as a window
    fprintf(gnuplotPipe, "set xlabel 'Wavelength (nm)'\n");  // Set the x-axis label
    fprintf(gnuplotPipe, "set ylabel 'Intensity'\n");  // Set the y-axis label
    fprintf(gnuplotPipe, "set title 'Spectrum Analysis'\n");  // Set the graph title
    fprintf(gnuplotPipe, "plot '-' with lines title 'Intensity'\n");  // Begin plotting with lines and a title

    // Plot the intensity values
    for (int col = 0; col < imageWidth; col++) {
        double wavelength = minWavelength + col * wavelengthStep;
        fprintf(gnuplotPipe, "%f %d\n", wavelength, intensities[col]);
    }
    fprintf(gnuplotPipe, "e\n");  // End of data marker for Gnuplot

    fflush(gnuplotPipe);  // Flush the pipe to ensure all data is written
    pclose(gnuplotPipe);  // Close the Gnuplot pipe

    // Free allocated memory
    free(intensities);
    for (int row = 0; row < imageHeight; row++) {
        free(image[row]);
    }
    free(image);

    return 0;
}
