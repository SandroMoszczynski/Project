from squab_call import squab_call
from squab_read import squab_read

squab_call(1)
#x = squab_read("Default0012")
#print(x[0,1])


# action  = d,v,p1,p1

# p = face
# v = vertex
# observation = percept = an adjacency matrix

# av matrix = [
#     0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
# 0   0 1 1 
# 1   1 0 0 1
# 2   1 0 0
# 3   0 1
# 4   0
# 5   0
# 6   0
# 7   0
# 8   0
# 9   0
# 10  0
# 11  0
# 12  0
# 13  0
# 14  0
# 15  0
            
        #     		self.num_percepts_list = np.array([4,4]) # figure out why this needs to be 4x4 and if i need to change it
		# self.gamma_damping = gamma_damping
		# self.eta_glow_damping = eta_glow_damping
		# self.policy_type = policy_type
		# self.beta_softmax = beta_softmax
		# self.num_reflections = num_reflections
		# self.possible_moves = np.array([[0,0,2,3],[0,0,1,3],[0,1,3,5],[0,1,4,5],[0,4,5,7],[0,4,6,7],[0,5,10,11],[0,5,7,11],
		# [0,2,8,9],[0,2,3,9],[0,8,12,13],[0,8,9,13],[0,9,13,14],[0,9,10,14],[0,10,14,15],[0,10,11,15],[1,0,2,3],[1,0,1,3],
		# [1,1,3,5],[1,1,4,5],[1,4,5,7],[1,4,6,7],[1,5,10,11],[1,5,7,11],[1,2,8,9],[1,2,3,9],[1,8,12,13],[1,8,9,13],
		# [1,9,13,14],[1,9,10,14],[1,10,14,15],[1,10,11,15]])
		# self.num_actions = len(self.possible_moves)
		
		# #self.num_percepts = int(np.prod(np.array(self.num_percepts_list).astype(np.float64))) # total number of possible percepts
		# self.num_percepts = self.possible_moves.size