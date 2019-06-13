from gurobipy import *

n = int(input())
H, W = input().split()
H = int(H)
W = int(W)

h = []
w = []

for i in range(n):
	h_, w_ = input().split()
	h.append(int(h_))
	w.append(int(w_))

model = Model("bin_packing_2D")
model.setParam("TimeLimit", 60)

q = []
for i in range(n):
	q.append(model.addVar(vtype=GRB.BINARY, name="q[" + str(i) + "]"))

y = []
for i in range(n):
	y.append(model.addVar(vtype=GRB.BINARY, name="y[" + str(i) + "]"))

x = []
for i in range(n):
	x.append([])
	for j in range(n):
		x[-1].append(model.addVar(vtype=GRB.BINARY, name="x[" + str(i) + "][" + str(j) + "]"))

z = []
for i in range(n):
	z.append([])
	for j in range(n):
		z[-1].append(model.addVar(vtype=GRB.BINARY, name="z[" + str(i) + "][" + str(j) + "]"))


obj = 0
for i in range(n):
	obj += q[i]

model.setObjective(obj, GRB.MINIMIZE)

for j in range(n):
	constr = y[j]
	for i in range(j - 1):
		constr += x[i][j]
	model.addConstr(constr == 1, "c[" + str(j) + "]")

for i in range(n - 1):
	constr = 0
	for j in range(i + 1, n):
		constr += w[j] * x[i][j]
	model.addConstr(constr <= (W - w[i]) * y[i], "d[" + str(i) + "]")

for i in range(n):
	constr = q[i]
	for k in range(i - 1):
		constr += z[k][i]
	model.addConstr(constr == y[i], "e[" + str(i) + "]")

for k in range(n - 1):
	constr = 0
	for i in range(k + 1, n):
		constr += h[i] * z[k][i]
	model.addConstr(constr <= (H - h[k]) * q[k], "f[" + str(k) + "]")
	
model.optimize()

for v in model.getVars():
	if v.x > 0.5: print(v.varName)

print('Obj: ' + str(model.objVal))
