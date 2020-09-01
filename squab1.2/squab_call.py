from subprocess import Popen, PIPE, STDOUT
from squab_read import squab_read
import time

#need to maybe make a way to link the compute time with the read time
#probably solved this with the while loop in read, will now wait between iterations 
#and delete inputs, now works in non commandline applications


def squab_call(action, joints=4, x_size = 5, y_size = 3, param_a = 0, param_b = 0.3, param_c = 0.01, duration = 10000):
    # squab = ["./squab"]
    # run_squab = Popen(squab,stdin=PIPE)
    # #, stdout=PIPE)
    # run_squab.stdin.write(b"Load Default ")
    # #tiling = "Tiling " + str(joints) + " " + str(x_size) + " " + str(y_size)
    # #tiling_as_string = str.encode(tiling)
    # #run_squab.stdin.write(tiling_as_string)
    # #print("Tiling Complete")
    # time.sleep(1)
    # report = "Report " + str(param_a) + " " + str(param_b) + " " + str(param_c)+ " " + str(duration)
    # report_as_string = str.encode(report)
    # run_squab.stdin.write(report_as_string)
    # #print("Generate Report")
    # run_squab.stdin.write(b"Quit")
    # #print("Quitting")
    # run_squab.stdin.close()
    # #run_squab.stdout.close()
    # run_squab.wait()
    current_dimensions = "Default"
    squab = ["./squab"]
    run_squab = Popen(squab, stdin=PIPE, stdout=PIPE)
    command_load = ("Load " + str(current_dimensions) + " ")
    command_load_as_string = str.encode(command_load)
    run_squab.stdin.write(command_load_as_string)
    if action[0] == 0:
        run_squab.stdin.write(b"Draw")
    else:
        run_squab.stdin.write(b"DrawDual")
    command_run = ("AddFace 3 " + str(action[1]) + " " + str(action[2]) + " " +str(action[3]) + " ")
    command_run_as_string = str.encode(command_run)
    run_squab.stdin.write(command_run_as_string)
    save_name = (str(current_dimensions) + str(action[1]) + str(action[2]) +str(action[3]))
    command_save = ("Save " + str(save_name) + " ")
    command_save_as_string = str.encode(command_save)
    run_squab.stdin.write(command_save_as_string)
    run_squab.stdin.write(b"Report 0 0.3 0.01 1000")
    run_squab.stdin.write(b"Quit")
    run_squab.stdin.close()
    run_squab.stdout.close()
    run_squab.wait()
    squab_outcome = squab_read(current_dimensions)
    print(squab_outcome[0,1])

