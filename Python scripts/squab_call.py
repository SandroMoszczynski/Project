from subprocess import Popen, PIPE, STDOUT

#need to maybe make a way to link the compute time with the read time
#probably solved this with the while loop in read, will now wait between iterations 
#and delete inputs, now works in non commandline applications


def squab_call(joints=4, x_size = 5, y_size = 3, param_a = 0, param_b = 0.3, param_c = 0.01, duration = 10000):
    squab = ["../squab1.2/./squab"]
    run_squab = Popen(squab,stdin=PIPE, stdout=PIPE)
    tiling = "Tiling " + str(joints) + " " + str(x_size) + " " + str(y_size)
    tiling_as_string = str.encode(tiling)
    run_squab.stdin.write(tiling_as_string)
    #print("Tiling Complete")
    report = "Report " + str(param_a) + " " + str(param_b) + " " + str(param_c)+ " " + str(duration)
    report_as_string = str.encode(report)
    run_squab.stdin.write(report_as_string)
    #print("Generate Report")
    run_squab.stdin.write(b"Quit")
    #print("Quitting")
    run_squab.stdin.close()
    run_squab.stdout.close()



