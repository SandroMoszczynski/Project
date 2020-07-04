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
        # hopefully this wont be too resource intensive, might need to put a wait commmand in
        filename = glob.glob("results/runtimes**.txt") # searches for the file with run time inside it
        time.sleep(0.1)
    if filename != 0:
        result = np.genfromtxt(filename[0], delimiter = " ", dtype=[('f0', '<i8'), ('f1', '<i8'), ('f2', '<f8')]) 
        results = [filename[0],result['f0'].item(0),result['f1'].item(0),result['f2'].item(0)]
    os.remove(filename[0])    # deletes used file
    while not extrafiles:
        extrafiles=glob.glob("reports/bench_*.pdf") #need to wait for pdf creation
        time.sleep(0.1)
    if extrafiles != 0: 
        extrafiles += glob.glob("reports/**.tex")
        extrafiles += glob.glob("results/**.txt")
        for i in range(len(extrafiles)): 
            os.remove(extrafiles[i])   #deletes all extra files
    return results