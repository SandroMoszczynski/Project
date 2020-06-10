import glob
import numpy as np

#note that this just reads every file with runtimes

def squab_read():
    results = []
    filenames = glob.glob("results/runtimes**.txt")
    for i in range(len(filenames)):
        result = np.genfromtxt(filenames[i], delimiter = " ", dtype=[('f0', '<i8'), ('f1', '<i8'), ('f2', '<f8')])
        appendable = [filenames[i],result['f0'].item(0),result['f1'].item(0),result['f2'].item(0)]
        results.append(appendable)    
    return results