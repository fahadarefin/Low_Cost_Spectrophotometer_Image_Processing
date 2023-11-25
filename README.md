Sure, I'll provide you with a guide to use the script and then add it as version 2.0 to an existing GitHub repository.

### Guide to Use the Spectrum Analysis Script

#### Prerequisites:
- Python installed on your machine.
- Required Python packages installed (NumPy, Matplotlib, SciPy).

#### Steps:

1. **Clone the Repository:**
   If you haven't already, clone the GitHub repository to your local machine. Open a terminal and run:

   ```bash
   git clone <repository_url>
   cd <repository_directory>
   ```

2. **Install Dependencies:**
   Make sure you have the required Python packages installed. You can install them using:

   ```bash
   pip install numpy matplotlib scipy
   ```

3. **Run the Script:**
   Place your TXT files containing the spectrum data in a directory. Now, run the script by executing:

   ```bash
   python spectrum_analysis_script.py
   ```

4. **Select TXT Files:**
   A file dialog will appear, allowing you to select one or more TXT files. Choose at least two files for before and after measurements.

5. **Analysis and Plotting:**
   The script will read the data from the selected files, calculate absorbance, and plot the absorbance spectrum. Optionally, you can choose to mark the max peak and apply signal smoothing.

6. **Output:**
   The script will save the generated plot as `absorbance_spectrum.jpg` and display the plot. You can find the plot in the same directory as the script.
