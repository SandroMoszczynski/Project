from subprocess import Popen, PIPE, STDOUT

#need to maybe make a way to link the compute time with the read time
#probably solved this with the while loop in read, will not wait between iterations 
#and delete inputs, note this seems to not work with ipython untill it exits the 
#application, will have to see how this runs later


def squab_call( joints=4,x_size = 5,y_size = 3):
    squab = ["./squab"]
    run_squab = Popen(squab,stdin=PIPE , stdout=PIPE, stderr = PIPE)
    tiling = "Tiling " + str(joints) + " " + str(x_size) + " " + str(y_size)
    tiling_as_string = str.encode(tiling)
    run_squab.stdin.write(tiling_as_string)
    print("Tiling Complete")
    run_squab.stdin.write(b"Report 0 0.3 0.01 1000")
    print("Generate Report")
    run_squab.stdin.write(b"Quit")
    print("Quitting")
    return ("Code inputted")


def squab_call_test():   
    squab = ["./squab"]
    run_squab_test = Popen(squab,stdin=PIPE , stdout=PIPE, stderr = PIPE)
    run_squab_test.stdin.write(b"Tiling 4 5 3")
    print("Tiling Complete")
    run_squab_test.stdin.write(b"Report 0 0.3 0.01 1000")
    print("Generate Report")
    run_squab_test.stdin.write(b"Quit")
    print("Quitting")


