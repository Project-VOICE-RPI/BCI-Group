#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <filesystem>

std::vector<float> splitLine(const std::string& line) {
    std::vector<float> values;
    std::stringstream ss(line);
    std::string token;

    while (std::getline(ss, token, ',')) {
        token.erase(0, token.find_first_not_of(" \t"));
        token.erase(token.find_last_not_of(" \t") + 1);

        if (!token.empty() && (std::isdigit(token[0]) || token[0] == '-' || token[0] == '.')) {
            values.push_back(std::stof(token));
        }
    }
    return values;
}

int main() {
    std::string fileName = "nirs_array.json";
    std::ifstream file(fileName);
    std::vector<int> labels;
    std::vector<std::vector<float>> features;

    if (!file.is_open()) {
        std::cerr << "Could not open file " << fileName << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        line.erase(std::remove(line.begin(), line.end(), '['), line.end());
        line.erase(std::remove(line.begin(), line.end(), ']'), line.end());

        // Split the line into the label (first value) and feature values (rest)
        std::vector<float> row = splitLine(line);
        
        if (row.size() > 1) {
            labels.push_back(static_cast<int>(row[0]));  // First value is the label
            row.erase(row.begin());  // Remove the label from feature list
            features.push_back(row); // Add remaining values as features
        }
    }

    file.close();

    // Prepare LIBSVM formatted data and write to file
    std::string outputFilePath = "libsvm/train_data.txt";
    std::ofstream outfile(outputFilePath);

    for (size_t i = 0; i < features.size(); ++i) {
        outfile << labels[i];  // Write the label
        for (size_t j = 0; j < features[i].size(); ++j) {
            outfile << " " << j + 1 << ":" << features[i][j];  // Format features as index:value
        }
        outfile << "\n";  // End of line for this sample
    }

    outfile.close();
    std::cout << "Data converted and saved in LIBSVM format!" << std::endl;

    return 0;
}
