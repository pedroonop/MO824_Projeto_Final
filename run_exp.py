import os

mode = int(argv[1])

k = 10
classes = 6
ns = []

if mode == 1: ns = [20, 40]
elif mode == 2: ns = [60,80]
else: ns = [100]

for classe in range(1, classes+1):
	for n in ns:
		for k_ in range(k):
			path = str(classe) + "/" + str(n) + "/" + str(k_)
			os.system("./ts_bin_packing2D <instances/" + path + " >results/" + path)
			os.system("./ts_bin_packing2D_diversification <instances/" + path + " >results_/" + path)
