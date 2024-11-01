#include "TestModSignalProcessing.h"
#include <fstream>
#include <iostream>
#include <vector>

void convertSnirfToDat(const std::string& snirfFile, const std::string& datFile) {
    // Open the .snirf file for reading
    std::ifstream inputFile(snirfFile);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << snirfFile << std::endl;
        return;
    }

    // Open the .dat file for writing
    std::ofstream outputFile(datFile);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file: " << datFile << std::endl;
        return;
    }

    std::string line;
    // Read each line of the .snirf file and write it to the .dat file
    while (std::getline(inputFile, line)) {
        // Write the line to the .dat file
        outputFile << line << std::endl;
    }

    // Close the files
    inputFile.close();
    outputFile.close();
}

int main() {
    // Define the .snirf file and .dat file names
    std::string snirfFile = "sample_nirs_data.snirf";
    std::string datFile = "sample_nirs_data.dat";       // Output .dat file name

    convertSnirfToDat(snirfFile, datFile);
    std::cout << "Conversion complete: " << datFile << " created." << std::endl;

    return 0;
}
