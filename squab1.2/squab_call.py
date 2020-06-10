from subprocess import Popen, PIPE, STDOUT

#need to maybe make a way to link the compute time with the read time

def squab_call(no_runs):   
    squab = ["./squab"]
    for i in range(no_runs):
        call_squab = Popen(squab,stdin=PIPE , stdout=PIPE, stderr = PIPE)
        tiling = "Tiling 4 " + str(i+1) + " " + str(i+1)
        tiling_as_b = str.encode(tiling)
        call_squab.stdin.write(tiling_as_b)
        print("Tiling Complete")
        call_squab.stdin.write(b"Report 0 0.3 0.01 1000")
        print("Generate Report")
        call_squab.stdin.write(b"Quit")
        print("Quitting")


