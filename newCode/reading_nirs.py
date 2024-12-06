import h5py
import numpy as np
import os
import json

folderPath = "../BCI2000/data/samplefiles/snirf_data"
big_data = []

if (not os.path.exists(folderPath)):
	print("Could not open the folder at {}".format(folderPath))
	exit(1)

for file in os.scandir(folderPath):
    filePath = file.path
    print("File {}".format(filePath))
    
    with h5py.File(filePath, 'r') as dat:
        d1 = np.array(dat.get('/nirs/data1/dataTimeSeries'))
        big_data.append(d1.tolist())

with open('nirs_array.json', 'w') as f:
    json.dump(big_data, f)
    
print("Sucessfully created json")