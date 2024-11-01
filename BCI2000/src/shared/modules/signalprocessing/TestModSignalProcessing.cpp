#include "TestModSignalProcessing.h"
#include <H5Cpp.h>
#include <vector>

int main() {
    H5::H5File file("path_to_file.snirf", H5F_ACC_RDONLY);
    H5::DataSet dataset = file.openDataSet("/nirs/data1/dataTimeSeries");

    // Retrieve dataset dimensions, create a buffer, and read data
    H5::DataSpace dataspace = dataset.getSpace();
    hsize_t dims[2];
    dataspace.getSimpleExtentDims(dims, NULL);
    std::vector<double> data(dims[0] * dims[1]);
    dataset.read(data.data(), H5::PredType::NATIVE_DOUBLE);

    // Save or process data here
    file.close();
    return 0;
}
