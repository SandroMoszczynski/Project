#from squab_call import squab_call
from squab_read import squab_read


x = squab_read("Default")
print(x[0,1])


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
            