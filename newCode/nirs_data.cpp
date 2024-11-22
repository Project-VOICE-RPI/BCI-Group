#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

int main(){
    std::string folderPath = "../BCI2000/data/samplefiles/snirf_data";
    
    if (!fs::exists(folderPath)){
        std::cerr << "Could not open the folder at: " << folderPath << std::endl;
        return 1;
    }

    for (const auto& entry : fs::directory_iterator(folderPath)) {

        if (fs::is_regular_file(entry)) {
            std::string filePath = entry.path().string();
            std::cout << "Opening file: " << filePath << std::endl;

            std::ifstream file(filePath);
            char header[100];
            file.read(header, sizeof(header));

            std::cout << "Header read: " << std::endl;
            for (int i = 0; i < 100; ++i) {
                std::cout << header[i]; 
            }
            std::cout << "\n";

            file.close();
        }
    }

    return 0;
}