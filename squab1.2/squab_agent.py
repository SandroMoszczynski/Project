import __future__
import numpy as np

# -*- coding: utf-8 -*-
"""
Copyright 2018 Alexey Melnikov and Katja Ried.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License.
Please acknowledge the authors when re-using this code and maintain this notice intact.
Code written by Alexey Melnikov and Katja Ried, implementing ideas from 
'Projective simulation for artificial intelligence'
Hans J. Briegel & Gemma De las Cuevas
Scientific Reports 2, Article number: 400 (2012) doi:10.1038/srep00400
and 
'Projective Simulation for Classical Learning Agents: A Comprehensive Investigation'
Julian Mautner, Adi Makmal, Daniel Manzano, Markus Tiersch & Hans J. Briegel
New Generation Computing, Volume 33, Issue 1, pp 69-114 (2015) doi:10.1007/s00354-015-0102-0
"""
class squab_agent(object):
	"""Projective Simulation agent with two-layered network. Features: forgetting, glow, reflection, optional softmax rule. """
	
	def __init__(self, gamma_damping, eta_glow_damping, policy_type, beta_softmax, num_reflections):
		"""Initialize the basic PS agent. Arguments: 
            - num_actions: integer >=1, 
            - num_percepts_list: list of integers >=1, not nested, representing the cardinality of each category/feature of percept space.
            - gamma_damping: float between 0 and 1, controls forgetting/damping of h-values
            - eta_glow_damping: float between 0 and 1, controls the damping of glow; setting this to 1 effectively switches off glow
            - policy_type: string, 'standard' or 'softmax'; toggles the rule used to compute probabilities from h-values
            - beta_softmax: float >=0, probabilities are proportional to exp(beta*h_value). If policy_type != 'softmax', then this is irrelevant.
            - num_reflections: integer >=0 setting how many times the agent reflects, ie potentially goes back to the percept. Setting this to zero effectively deactivates reflection.
            """
		
		
		self.num_percepts_list = np.array([1,1]) # figure out why this needs to be 4x4 and if i need to change it
		self.gamma_damping = gamma_damping
		self.eta_glow_damping = eta_glow_damping
		self.policy_type = policy_type
		self.beta_softmax = beta_softmax
		self.num_reflections = num_reflections
		self.possible_moves = np.array([[0,2,3],[0,1,3],[1,3,5],[1,4,5],[4,5,7],[4,6,7],[5,10,11],[5,7,11],[2,8,9],
		[2,3,9],[8,12,13],[8,9,13],[9,13,14],[9,10,14],[10,14,15],[10,11,15]])
		self.num_actions = len(self.possible_moves)
		
		self.num_percepts = int(np.prod(np.array(self.num_percepts_list).astype(np.float64))) # total number of possible percepts
		
		self.h_matrix = np.ones((self.num_actions, self.num_percepts), dtype=np.float64) #Note: the first index specifies the action, the second index specifies the percept.
		self.g_matrix = np.zeros((self.num_actions, self.num_percepts), dtype=np.float64) #glow matrix, for processing delayed rewards
		
		if num_reflections > 0:
			self.last_percept_action = None  #stores the last realized percept-action pair for use with reflection. If reflection is deactivated, all necessary information is encoded in g_matrix.
			self.e_matrix = np.ones((self.num_actions, self.num_percepts), dtype=np.bool_) # emoticons
                #emoticons are initialized to True (happy, good choice) and set to false (sad, reflect again) only if the percept-action pair is used and does not yield a reward.
			
	def percept_preprocess(self, observation): # preparing for creating a percept
		"""Takes a multi-feature percept and reduces it to a single integer index.
		Input: list of integers >=0, of the same length as self.num_percept_list; 
			respecting the cardinality specified by num_percepts_list: observation[i]<num_percepts_list[i] (strictly)
			Output: single integer."""
		percept = 0
		if len(observation) == 6:
			percept = 0
		else:
			for which_feature in range(len(observation)-7):
				print(observation[which_feature+7])
				percept += int(observation[which_feature+7] * np.prod(self.num_percepts_list[:which_feature]))
		return percept

	def reset_actions(self):
		self.possible_moves = np.array([[0,2,3],[0,1,3],[1,3,5],[1,4,5],[4,5,7],[4,6,7],[5,10,11],[5,7,11],[2,8,9],
		[2,3,9],[8,12,13],[8,9,13],[9,13,14],[9,10,14],[10,14,15],[10,11,15]])
		return self.possible_moves
		
	def deliberate_and_learn(self, observation, reward):
			#this is where it either moves or loads from mememory, so must load the saved percept
			#currently only allows normal lattice formation, not dual, well get there, need to make it want
			#to only use the possible moves once for each type
		"""Given an observation and a reward (from the previous interaction), this method
		updates the h_matrix, chooses the next action and records that choice in the g_matrix and last_percept_action.
		Arguments: 
			- observation: list of integers, as specified for percept_preprocess, 
			- reward: float
		Output: action, represented by a single integer index."""        
		self.h_matrix =  self.h_matrix - self.gamma_damping * (self.h_matrix - 1.) + self.g_matrix * reward # learning and forgetting
		if (self.num_reflections > 0) and (self.last_percept_action != None) and (reward <= 0): # reflection update
			self.e_matrix[self.last_percept_action] = 0
		percept = self.percept_preprocess(observation) 
		rnd_choice = np.random.choice(len(self.possible_moves), p=self.probability_distr(percept)) #deliberate once
		action = [np.random.choice(1),self.possible_moves[rnd_choice][0],self.possible_moves[rnd_choice][1],self.possible_moves[rnd_choice][2]]
		np.delete(self.possible_moves,rnd_choice,0)
		for _ in range(self.num_reflections):  #if num_reflection >=1, repeat deliberation if indicated
			if self.e_matrix[action, percept].any():
				break
			rnd_choice = np.random.choice(len(self.possible_moves), p=self.probability_distr(percept)) #deliberate once
			action = [np.random.choice(1),self.possible_moves[rnd_choice][0],self.possible_moves[rnd_choice][1],self.possible_moves[rnd_choice][2]]
			np.delete(self.possible_moves,rnd_choice,0)		
		self.g_matrix = (1 - self.eta_glow_damping) * self.g_matrix
		self.g_matrix[action, percept] = 1 #record latest decision in g_matrix
		if self.num_reflections > 0:
			self.last_percept_action = action, percept	#record latest decision in last_percept_action
		return action	
		
	def probability_distr(self, percept):
		"""Given a percept index, this method returns a probability distribution over actions
        (an array of length num_actions normalized to unit sum) computed according to policy_type."""        
		if self.policy_type == 'standard': #can probably remove this later
			h_vector = self.h_matrix[:, percept]
			probability_distr = h_vector / np.sum(h_vector)
		elif self.policy_type == 'softmax':
			h_vector = self.beta_softmax * self.h_matrix[:, percept]
			h_vector_mod = h_vector - np.max(h_vector)
			probability_distr = np.exp(h_vector_mod) / np.sum(np.exp(h_vector_mod))
		return probability_distr