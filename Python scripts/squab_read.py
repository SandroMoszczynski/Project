import glob
import numpy as np
import os
import time

def squab_read():
    print("reading")
    results = []
    filename = []    
    extrafiles = []
    while not filename: #important as some runs take a while to load, 
        filename = glob.glob("../squab1.2/results/runtimes**.txt") # searches for the file with run time inside it
        time.sleep(0.1)
    if filename != 0:
        result = np.genfromtxt(filename[0], delimiter = " ", dtype=[('f0', '<i8'), ('f1', '<i8'), ('f2', '<f8')]) 
        results = [filename[0],result['f0'].item(0),result['f1'].item(0),result['f2'].item(0)]
    os.remove(filename[0])    # deletes used file
    while not extrafiles:
        extrafiles=glob.glob("../squab1.2/reports/bench_*.pdf") #pdf creation is the slowest part
        time.sleep(0.1)
    if extrafiles != 0: 
        extrafiles += glob.glob("../squab1.2/reports/**.tex")
        extrafiles += glob.glob("../squab1.2/results/**.txt")
        for i in range(len(extrafiles)): 
            os.remove(extrafiles[i])   #deletes all extra files
    return results