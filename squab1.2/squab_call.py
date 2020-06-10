from subprocess import Popen, PIPE, STDOUT

squab = ["./squab"]

for i in range(10):
    call_squab = Popen(squab,stdin=PIPE , stdout=PIPE, stderr = PIPE)
    tiling = "Tiling 4 " + str(i+1) + " " + str(i+1)
    tiling_as_b = str.encode(tiling)
    call_squab.stdin.write(tiling_as_b)
    print("Tiling Complete")
    call_squab.stdin.write(b"Report 0 0.3 0.01 1000")
    print("Generate Report")
    call_squab.stdin.write(b"Quit")
    print("Quitting")


