import sys
import os
classe = sys.argv[1]
n = sys.argv[2]
seed = sys.argv[3]

os.system("touch temp")
os.system("echo " + classe + " " + n + " " + seed + " >temp")
os.system("./instance_generator <temp >instance")
os.system("rm temp")
os.system("./ts_bin_packing2D <instance")
