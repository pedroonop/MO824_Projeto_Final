import os

k = 10
classes = 6
ns = [20, 40, 60, 80, 100]

for classe in range(1, classes+1):
	for n in ns:
		for seed in range(k):
			os.system("touch temp")
			os.system("echo " + str(classe) + " " + str(n) + " " + str(seed) + " >temp")
			os.system("./instance_generator <temp >instances/" + str(classe) + "/" + str(n) + "/" + str(seed))
			os.system("rm temp")
