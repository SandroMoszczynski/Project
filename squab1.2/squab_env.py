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
        self.desired_outcome = 0.03
        self.current_dimensions = "Default"

    def reset(self):
        """resets x and y size to initial values"""
        #print("resetting")
        self.current_dimensions = "Default"
        return self.current_dimensions #needs to be the current state of the code
		
    def move(self, action):
        """calls the squab program and then reads it"""
        squab = ["./squab"]
        run_squab = Popen(squab, stdin=PIPE, stdout=PIPE)
        command_load = ("Load " + str(self.current_dimensions) + " ")
        command_load_as_string = str.encode(command_load)
        run_squab.stdin.write(command_load_as_string)
        if action[0] == 0:
            run_squab.stdin.write(b"Draw")
        else:
            run_squab.stdin.write(b"DrawDual")
        command_run = ("AddFace 3 " + str(action[1]) + " " + str(action[2]) + " " +str(action[3]) + " ")
        command_run_as_string = str.encode(command_run)
        run_squab.stdin.write(command_run_as_string)
        save_name = (str(self.current_dimensions) + str(action[0]) + str(action[1]) + str(action[2]) +str(action[3]))
        command_save = ("Save " + str(save_name) + " ")
        command_save_as_string = str.encode(command_save)
        run_squab.stdin.write(command_save_as_string)
        run_squab.stdin.write(b"Report 0 0.3 0.01 1000")
        run_squab.stdin.write(b"Quit")
        run_squab.stdin.close()
        run_squab.stdout.close()
        run_squab.wait()
        squab_outcome = squab_read(self.current_dimensions)
        #print("read")
        if squab_outcome[0,1] <= self.desired_outcome :
            reward = 1
        else:
            reward = 0
        step_finished = True
        self.current_dimensions = save_name
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
    agent = squab_agent(agent_config[0], agent_config[1], agent_config[2], agent_config[3], agent_config[4])
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
            self.agent.reset_actions()
            for t in range(max_steps_per_trial):
                discretized_observation, reward, done = self.single_interaction_step(discretized_observation, reward)
                reward_trial += reward
                if done:
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
			reward_trial_list = np.zeros(self.num_agents) #additive counter of the total rewards earned during the current trial, by each agent separately
			next_observation = self.env.reset() #percept for a single agent, the one which is up next
			"""Memo: environments for multiple agents should 
                take num_agents as (one of the) initialization parameter(s). The method move should take
                an agent_index as a parameter, along with a single action, 
                and return a single new percept for the next agent along with the reward for the current one."""
			for t in range(max_steps_per_trial):
				for i_agent in range(self.num_agents):
					action = self.agent_list[i_agent].deliberate_and_learn(next_observation, reward_list[i_agent])
					next_observation, reward_list[i_agent], done = self.env.move(i_agent, action)
					reward_trial_list[i_agent] += reward_list[i_agent]
					if done:
						break
			learning_curve[i_trial] = reward_trial_list/(t+1)
		return learning_curve
