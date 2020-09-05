from subprocess import Popen, PIPE, STDOUT
from squab_read import squab_read
import time
import numpy as np

#need to maybe make a way to link the compute time with the read time
#probably solved this with the while loop in read, will now wait between iterations 
#and delete inputs, now works in non commandline applications


def squab_call(move, joints=4, x_size = 5, y_size = 3, param_a = 0, param_b = 0.3, param_c = 0.01, duration = 10000):
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
    desired_outcome = 0.03
    current_dimensions = "D"
    no_moves = 0
    print(move)
    possible_moves = np.array([[0,0,2,1],[0,0,1,3],[0,1,3,5],[0,1,4,5],[0,4,5,7],[0,4,6,7],[0,5,10,11],[0,5,7,11],
    [0,2,8,9],[0,2,3,9],[0,8,12,13],[0,8,9,13],[0,9,13,14],[0,9,10,14],[0,10,14,15],[0,10,11,15],[1,0,2,3],[1,0,1,3],
    [1,1,3,5],[1,1,4,5],[1,4,5,7],[1,4,6,7],[1,5,10,11],[1,5,7,11],[1,2,8,9],[1,2,3,9],[1,8,12,13],[1,8,9,13],
    [1,9,13,14],[1,9,10,14],[1,10,14,15],[1,10,11,15]])
    num_actions = possible_moves.size
    #"""calls the squab program and then reads it"""
    print("action",move)
    action = possible_moves[move]
    np.delete(possible_moves,move,0)	
    squab = ["./squab"]
    run_squab = Popen(squab, stdin=PIPE, stdout=PIPE, stderr=PIPE)
    command_load = ("Load " + str(current_dimensions) + " ")
    if action[0] == 0:
        command_face = "Draw "
    else:
        command_face = "DrawDual "
    command_add = ("AddFace 3 " + str(action[1]) + " " + str(action[2]) + " " +str(action[3]) + " ")
    if no_moves == 20:
        save_name = str("B") + str(move)
    else:    
        save_name = str(current_dimensions) + str(move)
    command_save = ("Save " + str(save_name) + " ")
    command_report = "Report 0 0.3 0.01 10000 "
    command_quit = "Quit"
    test_input = str(command_load) + str(command_face) + str(command_add) + str(command_save) +str(command_report) + str(command_quit)
    test_input_as_string = str.encode(test_input)
    run_squab.stdin.write(test_input_as_string)
    std_out,std_err = run_squab.communicate()
    if run_squab.returncode != 0:
        run_squab.stdin.close()
        run_squab.stdout.close()
        run_squab.stderr.close()
        run_squab.wait()
        print("bad code")
    else:
        run_squab.stdin.close()
        run_squab.stdout.close()
        run_squab.stderr.close()
        run_squab.wait()
        #current_dimensions = save_name
        print(save_name)
        print("were here")
        squab_outcome = squab_read(current_dimensions)
        current_dimensions = save_name
        print(squab_outcome[0,1],desired_outcome)
        if squab_outcome[0,1] <= desired_outcome :
            reward = 1
            print("Target Reached")
            step_finished = True
        else:
            reward = 0
        step_finished = False

    no_moves += 1
    if no_moves == 37:
        print("max moves reached")
        step_finished = True
    print("move number",no_moves)
    

#not the codes fault :P getting a core dump
