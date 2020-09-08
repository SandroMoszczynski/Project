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
from squab_env import Interaction,Create_Agent,Create_Env,Interaction_Multiple
sys.path.insert(0, 'agents')
sys.path.insert(0, 'environments')
#create results folder if it doesn't exist already
if not os.path.exists('sim_results'): 
	os.makedirs('sim_results')
#import functions for initialising agents and environments, controlling their interaction etc

"""This is the master file, which calls other functions to create agents and environments and
run the interaction between them. It may range over different values of parameters,
recording learning data and ultimately saveing it in the results folder."""

"""Choose which agent and which environment you would like to use, from EnvList() and AgentList().
Note that the parameters specified below must match the required input formats of the chosen types.
(These requirements are specified in the docstrings of the respective classes.) """
#The option multiple_agents creates a situation where multiple agents inhabit a single environment.
# Only specific classes of environment support this. 

# performance evaluation
num_agents = 1
multiple_agents = False
#multiple_agents = True 

#When multiple_agents==False, the learning process is repeated with several independent agents in order to gather statistics.
# If multiple_agents==True, this is the number of agents interacting in a single environment
max_num_trials = 10  #Each agents get several attempts at completing a task, e.g. finding the goal in a maze or reaching the top in the mountain car problem
max_steps_per_trial = 25  #This parameter serves mostly to prevent agents getting stuck, since it terminates an attempt and resets the environment.


if not multiple_agents:
    n_param_scan = 1 #Loop over different values of a certain parameter to test which one works best
    average_param_performance = np.zeros(n_param_scan)
    for i_param_scan in range(n_param_scan):
        ps_eta = i_param_scan * 0.5 #set the ps_eta parameter to different values

        average_learning_curve = np.zeros(max_num_trials)  #this will record the rewards earned at each trial, averaged over all agents
        for i_agent in range(num_agents):	#train one agent at a time, and iterate over several agents	
            print("agent no",i_agent+1)
            env_config = 2, 1, max_num_trials  #need to pass the number of agents for a multi-agent environment
            env = Create_Env()
            num_action, gamma_damping, eta_glow_damping, policy_type, beta_softmax, num_reflections = env.possible_moves, 0, ps_eta, 'softmax', 1, 1
            agent_config = [num_action, gamma_damping, eta_glow_damping, policy_type, beta_softmax, num_reflections]
            agent = Create_Agent(agent_config)	
            interaction = Interaction(agent,env)
            learning_curve = interaction.single_learning_life(max_num_trials, max_steps_per_trial) #This function executes a 'learning life' between the agent and the environment
            average_learning_curve += learning_curve/num_agents
        average_param_performance[i_param_scan] = average_learning_curve[-1]  #The performance for a given value of the parameter is taken to be the average reward at the last trial.

elif multiple_agents:  #Here we do not iterate over a number of independent agents, but rather have them all in a single instance of the environment.
    
	n_param_scan = 1
	average_param_performance = np.zeros(n_param_scan)
	for i_param_scan in range(n_param_scan):
		ps_gamma = 0.5*i_param_scan
		env = Create_Env() 
		num_action, gamma_damping, eta_glow_damping, policy_type, beta_softmax, num_reflections = env.possible_moves, ps_gamma, 1, 'standard', 1, 0
		agent_config = [num_action, gamma_damping, eta_glow_damping, policy_type, beta_softmax, num_reflections]
		agent_list = []
		for i_agent in range(num_agents):	
			agent_list.append(Create_Agent(agent_config))
         
		interaction = Interaction_Multiple(agent_list, env)
		learning_curve = interaction.single_learning_life(max_num_trials, max_steps_per_trial)
		average_learning_curve = learning_curve.sum(axis=1)/num_agents
		average_param_performance[i_param_scan] = average_learning_curve[-1]

current_file_directory = os.path.dirname(os.path.abspath(__file__))
if num_agents == 1:
    np.savetxt(current_file_directory+'/sim_results'+'/h_matrix', agent.h_matrix, fmt='%.2f', delimiter=',')
    np.savetxt(current_file_directory+'/sim_results'+'/g_matrix', agent.h_matrix, fmt='%.3f', delimiter=',')
else:
	np.savetxt(current_file_directory+'/sim_results'+'/param_performance', average_param_performance, fmt='%.3f', delimiter=',')
np.savetxt(current_file_directory+'/sim_results'+'/learning_curve', average_learning_curve, fmt='%.3f', delimiter=',')


#only change the values in agent config in here, rest is handled by squab_env

