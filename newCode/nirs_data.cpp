#include <iostream>
#include <fstream>
#include <string>
#include <H5Cpp.h>

int main(){
    std::string filePath = "../BCI2000/data/samplefiles/sample_nirs_data1.snirf";
    
    try {
        H5::H5File file(filePath, H5F_ACC_RDONLY);

        std::cout << "File opened successfully: " << filePath << std::endl;

        H5::Group rootGroup = file.openGroup("/");
        std::cout << "Root group opened successfully." << std::endl;

        hsize_t numObjs = rootGroup.getNumObjs();
        for (hsize_t i = 0; i < numObjs; ++i) {
            std::string objName = rootGroup.getObjnameByIdx(i);
            std::cout << "Found object: " << objName << std::endl;
        }

    } catch (H5::FileIException &e) {
        std::cerr << "Error opening file: " << e.getDetailMsg() << std::endl;
        return -1;
    } catch (H5::Exception &e) {
        std::cerr << "HDF5 error: " << e.getDetailMsg() << std::endl;
        return -1;
    }
    //std::cout << filePath << std::endl;

    return 0;
}