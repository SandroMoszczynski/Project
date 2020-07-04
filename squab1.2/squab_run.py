# -*- coding: utf-8 -*-
"""
Copyright 2018 Alexey Melnikov and Katja Ried.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License.
Please acknowledge the authors when re-using this code and maintain this notice intact.
Code written by Alexey Melnikov and Katja Ried
"""

import __future__
import numpy as np
import os# for current directory
import sys # include paths to subfolders for agents and environments
from squab_agent import squab_agent # import the basic PS agent
from squab_read import squab_read #import the reader
from squab_call import squab_call #import the calling function
sys.path.insert(0, 'agents')
sys.path.insert(0, 'environments')
#create results folder if it doesn't exist already
if not os.path.exists('results'): 
	os.makedirs('results')
#import functions for initialising agents and environments, controlling their interaction etc

def CreateAgent(agent_name, agent_config = None):
	"""Given a name (string) and an optional config argument, this returns an agent.
	Agents must have a single method, deliberate_and_learn, which takes as input an observation 
	(list of integers) and a reward (float) and returns an action (single integer index)."""
	
	agent = squab_agent.BasicPSAgent(agent_config[0], agent_config[1], agent_config[2], agent_config[3], agent_config[4], agent_config[5], agent_config[6])
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


"""This is the master file, which calls other functions to create agents and environments and
run the interaction between them. It may range over different values of parameters,
recording learning data and ultimately saveing it in the results folder."""

"""Choose which agent and which environment you would like to use, from EnvList() and AgentList().
Note that the parameters specified below must match the required input formats of the chosen types.
(These requirements are specified in the docstrings of the respective classes.) """
env_name = 'Neverending_Color'
agent_name = 'PS-generalization'
#The option multiple_agents creates a situation where multiple agents inhabit a single environment.
# Only specific classes of environment support this. 
multiple_agents = False


# performance evaluation
num_agents = 100
#When multiple_agents==False, the learning process is repeated with several independent agents in order to gather statistics.
# If multiple_agents==True, this is the number of agents interacting in a single environment
max_num_trials = 100   #Each agents get several attempts at completing a task, e.g. finding the goal in a maze or reaching the top in the mountain car problem
max_steps_per_trial = 1000  #This parameter serves mostly to prevent agents getting stuck, since it terminates an attempt and resets the environment.



n_param_scan = 11  #Loop over different values of a certain parameter to test which one works best
average_param_performance = np.zeros(n_param_scan)
for i_param_scan in range(n_param_scan):
    ps_eta = i_param_scan * 0.1 #set the ps_eta parameter to different values

    average_learning_curve = np.zeros(max_num_trials)  #this will record the rewards earned at each trial, averaged over all agents
    for i_agent in range(num_agents):	#train one agent at a time, and iterate over several agents	
        env_config = 2, 1, max_num_trials  #need to pass the number of agents for a multi-agent environment
        env = squab_call(x_size,y_size,joints)
        num_actions, num_percepts_list, gamma_damping, eta_glow_damping, policy_type, beta_softmax, num_reflections = env.num_actions, env.num_percepts_list, 0, ps_eta, 'softmax', 1, 0
        agent_config = [num_actions, num_percepts_list, gamma_damping, eta_glow_damping, policy_type, beta_softmax, num_reflections]
        agent = CreateAgent(agent_name, agent_config)	
        interaction = squab_read()
        learning_curve = interaction.single_learning_life(max_num_trials, max_steps_per_trial) #This function executes a 'learning life' between the agent and the environment
        average_learning_curve += learning_curve/num_agents
    average_param_performance[i_param_scan] = average_learning_curve[-1]  #The performance for a given value of the parameter is taken to be the average reward at the last trial.

# Saving files
current_file_directory = os.path.dirname(os.path.abspath(__file__))
np.savetxt(current_file_directory+'/results'+'/h_matrix', agent.h_matrix, fmt='%.2f', delimiter=',')
np.savetxt(current_file_directory+'/results'+'/g_matrix', agent.h_matrix, fmt='%.3f', delimiter=',')
np.savetxt(current_file_directory+'/results'+'/learning_curve', average_learning_curve, fmt='%.3f', delimiter=',')