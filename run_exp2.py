import os

k = 10
classes = 6
ns = [20, 40, 60, 80, 100]

for classe in range(1, classes+1):
	for n in ns:
		for k_ in range(k):
			path = str(classe) + "/" + str(n) + "/" + str(k_)
			os.system("python ext.py <instances/" + path + " >results/ext/" + path)

