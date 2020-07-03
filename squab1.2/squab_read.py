import glob
import numpy as np
import os

#note that this just reads every file with runtimes

def squab_read():
    results = []
    filenames = []
    while not filenames: #important as some programs take a while to load, 
        # hopefully this wont be too resource intensive, might need to put a wait commmand in
        filenames = glob.glob("results/runtimes**.txt") # searches for the file with run time inside it
    if filenames != 0:
        result = np.genfromtxt(filenames[0], delimiter = " ", dtype=[('f0', '<i8'), ('f1', '<i8'), ('f2', '<f8')]) 
        appendable = [filenames[0],result['f0'].item(0),result['f1'].item(0),result['f2'].item(0)]
        results.append(appendable)    
        os.remove(filenames[0])   #deletes said file
    return results