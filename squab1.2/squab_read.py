import glob
import numpy as np

results = []
filenames = glob.glob("results/runtimes**.txt")

for i in range(len(filenames)):
    result = np.genfromtxt(filenames[i], delimiter = " ", dtype=[('f0', '<i8'), ('f1', '<i8'), ('f2', '<f8')])
    #print(result[0,1])
    appendable = [filenames[i],result['f0'].item(0),result['f1'].item(0),result['f2'].item(0)]
    print(appendable)
    results.append(appendable)    
print(results)