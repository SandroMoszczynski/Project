from subprocess import Popen, PIPE, STDOUT
from squab_read import squab_read
from squab_agent import squab_agent
import numpy as np
"""for personal edification later; creates and enviroment object, 
then interaction takes this enviroment class with members move and resset and
iterates each move, then resets when reward is reached"""

class TaskEnvironment(object):
    "creates an enviroment that interacts with squab, parameters need to be updated"

    def __init__(self):
        """create a bunch of parameters here, see squab call for param a,b,c
        current dimensions may need to be adjusted to work properly, need to follow through 
        to see if this gets updated in move or through the agent, probably the later"""
        self.desired_outcome = 0.01
        self.current_dimensions = "D"
        self.no_moves = 0
        self.possible_moves = np.array([[0,0,2,3],[0,2,0,1],[0,1,3,5],[0,3,1,5],[0,4,5,7],[0,5,4,6],[0,5,10,11],[0,10,5,7],
        [0,2,8,9],[0,8,2,3],[0,8,12,13],[0,12,8,9],[0,9,13,14],[0,14,15,11],[1,0,2,3],[1,2,0,1],[1,1,3,5],[1,3,1,5],
        [1,4,5,7],[1,5,4,6],[1,5,10,11],[1,10,5,7],[1,2,8,9],[1,8,2,3],[1,8,12,13],[1,12,8,9],[1,9,13,14],[1,14,15,11]])
        self.num_actions = self.possible_moves.size

    def reset(self):
        """resets x and y size to initial values"""
        self.current_dimensions = "D"
        self.no_moves = 0
        return self.current_dimensions #needs to be the current state of the code

    def reset_actions(self):
        self.possible_moves = np.array([[0,0,2,3],[0,2,0,1],[0,1,3,5],[0,3,1,5],[0,4,6,7],[0,5,4,6],[0,5,10,11],[0,10,5,7],
        [0,2,8,9],[0,8,2,3],[0,8,12,13],[0,12,8,9],[0,9,13,14],[0,14,15,11],[1,0,2,3],[1,2,0,1],[1,1,3,5],[1,3,1,5],
        [1,4,6,7],[1,5,4,6],[1,5,10,11],[1,10,5,7],[1,2,8,9],[1,8,2,3],[1,8,12,13],[1,12,8,9],[1,9,13,14],[1,14,15,11]])
        return self.possible_moves
		
    def move(self, move, agent_no = None):
        #"""calls the squab program and then reads it"""
        #print("action",move)
        action = self.possible_moves[move]
        np.delete(self.possible_moves,move,0)	
        command_load = ("Load " + str(self.current_dimensions) + " ")
        if action[0] == 0:
            command_face = "Draw "
        else:
            command_face = "DrawDual "
        command_add = ("AddFace 3 " + str(action[1]) + " " + str(action[2]) + " " +str(action[3]) + " ")
        if self.no_moves == 20:
            save_name = str("B") + str(move)
        else:    
            save_name = str(self.current_dimensions) + str(move)
        command_save = ("Save " + str(save_name) + " ")
        command_report = "Report 0 0.3 0.01 10000 "
        command_quit = "Quit"
        test_input = str(command_load) + str(command_face) + str(command_add) + str(command_save) +str(command_report) + str(command_quit)
        test_input_as_string = str.encode(test_input)
        squab = ["./squab"]
        run_squab = Popen(squab, stdin=PIPE, stdout=PIPE, stderr=PIPE)
        run_squab.stdin.write(test_input_as_string)
        std_out,std_err = run_squab.communicate()
        if run_squab.returncode != 0:
            run_squab.stdin.close()
            run_squab.stdout.close()
            run_squab.stderr.close()
            run_squab.wait()
            print("bad code")
            reward = 0
            step_finished = False
        else:
            run_squab.stdin.close()
            run_squab.stdout.close()
            run_squab.stderr.close()
            run_squab.wait()
            squab_outcome = squab_read(self.current_dimensions)
            self.current_dimensions = save_name
            print("current dim", self.current_dimensions)
            print("error rate: ", squab_outcome[0,5], "desidred error: ", self.desired_outcome)
            if squab_outcome[0,5] <= self.desired_outcome :
                reward = 1
                print("-------------Target Reached----------------")
                print("move taken: ", action)
                step_finished = True
            else:
                reward = 0
                step_finished = False
                print("move taken: ",action)
        self.no_moves += 1
        if self.no_moves == 37:
            print("max moves reached")
            step_finished = True
        print("move number",self.no_moves)
        return self.current_dimensions, reward, step_finished

def Create_Env():
    env = TaskEnvironment()
    return env

def Create_Agent(agent_config = None):
    """
    Given a name (string) and an optional config argument, this returns an agent.
    Agents must have a single method, deliberate_and_learn, which takes as input an observation 
    (list of integers) and a reward (float) and returns an action (single integer index).
    """
    agent = squab_agent(agent_config[0], agent_config[1], agent_config[2], agent_config[3], agent_config[4],agent_config[5])
    return agent

class Interaction(object):
	
    def __init__(self, agent, environment):
        """Set up an interaction (which is not actually run yet). Arguments: 
            agent: object possessing a method deliberate_and_learn, which takes as arguments (discretized_observation, reward) and returns action;
            environment: object possessing the following two methods:
                reset: no argument, returns a discretized_observation
                move: takes action as an argument and returns discretized_observation, reward, done"""
        self.agent = agent
        self.env = environment

    def single_learning_life(self, num_trials, max_steps_per_trial):
        """Train the agent over num_trials, allowing at most max_steps_per_trial 
        (ending the trial sooner if the environment returns done),
        and return an array containing the time-averaged reward from each trial."""
        learning_curve = np.zeros(num_trials)
        reward = 0 #temporarily stores the reward for the most recent action
        for i_trial in range(num_trials):
            reward_trial = 0 #additive counter of the total rewards earned during the current trial
            discretized_observation = self.env.reset()
            self.env.reset_actions()
            print("Trial no" , i_trial)
            for t in range(max_steps_per_trial):
                discretized_observation, reward, done = self.single_interaction_step(discretized_observation, reward)
                reward_trial += reward
                if done:
                    print("breaking")
                    break
            learning_curve[i_trial] = float(reward_trial)/(t+1)
        return learning_curve
		
    def single_interaction_step(self, discretized_observation, reward):
        action = self.agent.deliberate_and_learn(discretized_observation, reward)
        return self.env.move(action)

class Interaction_Multiple(object):
    
    def __init__(self, agent_list, environment):
        """Set up an interaction for multiple agents in parallel. Arguments: 
            agent_list: list of agents, which are objects possessing a method deliberate_and_learn, which takes as arguments (discretized_observation, reward) and returns action;
            environment: object possessing the following two methods:
            reset: no argument, returns a discretized_observation
            move: takes action as an argument and returns discretized_observation, reward, done"""
        self.agent_list = agent_list
        self.num_agents = len(agent_list)
        self.env = environment
        
    def single_learning_life(self, num_trials, max_steps_per_trial):
        """Train all agents over num_trials, allowing at most max_steps_per_trial 
        (ending the trial sooner if the environment returns done),
        and return an array containing the time-averaged rewards (?) from each trial."""
        learning_curve = np.zeros([num_trials, self.num_agents])
        reward_list = np.zeros(self.num_agents) #temporarily stores the most recent rewards earned by each agent
        for i_trial in range(num_trials):
            print("trial_no",i_trial)
            reward_trial_list = np.zeros(self.num_agents) #additive counter of the total rewards earned during the current trial, by each agent separately
            next_observation = self.env.reset() #percept for a single agent, the one which is up next
            self.env.reset_actions()
            """Memo: environments for multiple agents should 
                take num_agents as (one of the) initialization parameter(s). The method move should take
                an agent_index as a parameter, along with a single action, 
                and return a single new percept for the next agent along with the reward for the current one."""
            for t in range(max_steps_per_trial):
                for i_agent in range(self.num_agents):
                    print("agent no", i_agent)
                    action = self.agent_list[i_agent].deliberate_and_learn(next_observation, reward_list[i_agent])
                    next_observation, reward_list[i_agent], done = self.env.move(action,i_agent)
                    reward_trial_list[i_agent] += reward_list[i_agent]
                    if done:
                        print("breaking")
                        break
            learning_curve[i_trial] = reward_trial_list/(t+1)
        return learning_curve
