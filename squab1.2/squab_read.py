import glob
import numpy as np
import os
import time

def squab_read(save_name):# add it needs to read the name and upload it
    #print("reading")
    #results = []
    filename = []    
    extrafiles = []
    while not filename: #important as some runs take a while to load, 
        search_name = "results/perf_" + str(save_name) + "**.txt"
        filename = glob.glob(search_name) # searches for the file with run time inside it
        #time.sleep(0.1)
    if filename != 0:
        result = np.genfromtxt(filename[0], delimiter = " ") 
        #results = [filename[0],result['f0'].item(0),result['f1'].item(0),result['f2'].item(0)]
    os.remove(filename[0])    # deletes used file
    while not extrafiles:
        extrafiles=glob.glob("reports/bench_*.pdf") #pdf creation is the slowest part
        #time.sleep(0.5)
    if extrafiles != 0: 
        extrafiles += glob.glob("reports/**.tex")
        extrafiles += glob.glob("results/**.txt")
        for i in range(len(extrafiles)): 
            os.remove(extrafiles[i])   #deletes all extra files
    return result