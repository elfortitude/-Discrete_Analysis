import copy
import numpy as np

def fill_vectors(Matrix, n):
    a = []
    b = []
    c = []
    d = []
    a.append(0)
    b.append(Matrix[0][0])
    c.append(Matrix[0][1])
    d.append(Matrix[0][2])
    for i in range(1, n - 1):
        a.append(Matrix[i][0])
        b.append(Matrix[i][1])
        c.append(Matrix[i][2])
        d.append(Matrix[i][3])
    a.append(Matrix[n-1][0])
    b.append(Matrix[n-1][1])
    d.append(Matrix[n-1][2])
    c.append(0)
    return a, b, c, d

def straight_run(a, b, c, d, n):
    P = []
    Q = []
    p = (-1) * c[0] / b[0]
    P.append(p)
    q = d[0] / b[0]
    Q.append(q)
    if not(abs(b[0]) >= (abs(a[0]) + abs(c[0]))):
        print('error')
        exit(1)
    for i in range(1, n):
        # if (a[i] == 0 and i != (n-1)) or (c[i] == 0 and i != (n-1)) or not(abs(b[i] >= (abs(a[i]) + abs(c[i])))):
        #     print('error')
        #     exit(1)
        p = (-1) * c[i] / (b[i] + a[i] * P[i-1])
        P.append(p)
        q = (d[i] - a[i] * Q[i-1]) / (b[i] + a[i]*P[i-1])
        Q.append(q)
    return P, Q

def solve(P, Q, n):
    X = [0.0] * n
    X[n-1] = Q[n-1]
    for i in range(n-2, -1, -1):
        X[i] = ((-1) * c[i] / (b[i] + a[i] * P[i-1])) * X[i+1] + ((d[i] - a[i] * Q[i-1]) / (b[i] + a[i] * P[i-1]))
    return X


print("Input size of matrix: ")
n = int(input())
f = open('sample_2.txt', 'rt')

Matrix = []
count = 0

for line in f:
    Matrix.append(list(map(float, line.split())))
    count += 1
if count != n:
    print('error')
    exit(1)
a, b, c, d = fill_vectors(Matrix, n)
P, Q = straight_run(a, b, c, d, n)
X = solve(P, Q, n)

print("----------Start matrix:----------")
for i in range(n):
    print("%.3f | %.3f | %.3f | %.3f" % (a[i], b[i], c[i], d[i]))
print('\n')

print("----------P vector:----------")
for i in range(n):
    print("%.4f" % P[i])
print('\n')

print("----------Q vector:----------")
for i in range(n):
    print("%.4f" % Q[i])
print('\n')

print("----------SOLVE:----------")
for i in range(n):
    print("x[%d] = %.4f" % (i, X[i]))
print('\n')