import copy
import numpy as np

def     pivot_matrix(M):
    m = len(M)
    count = 0

    id_mat = [[float(i == j) for i in range(m)] for j in range(m)]

    for j in range(m):
        row = max(range(j, m), key=lambda i: abs(M[i][j]))
        if j != row:
            count += 1
            id_mat[j], id_mat[row] = id_mat[row], id_mat[j]
    return id_mat, count

def     decompose_to_LU(A, n):
    L = [[0] * n for i in range(n)]
    U = [[0] * n for i in range(n)]

    P, count = pivot_matrix(A)
    PA = matrixmult(P, A)

    for j in range(n):
        L[j][j] = 1
        for i in range(j+1):
            s1 = sum(U[k][j] * L[i][k] for k in range(i))
            U[i][j] = PA[i][j] - s1
        for i in range(j, n):
            s2 = sum(U[k][j] * L[i][k] for k in range(j))
            L[i][j] = (PA[i][j] - s2) / U[j][j]

    return (P, L, U, count)

def     matrixmult(M1,M2):
    sum = 0
    t = []
    M3 = []
    if len(M2) != len(M1[0]):
        print("Nope")
    else:
        r1 = len(M1)
        c1 = len(M1[0])
        r2 = c1
        c2 = len(M2[0])
        for z in range(0,r1):
            for j in range(0,c2):
                for i in range(0,c1):
                   sum = sum + M1[z][i] * M2[i][j]
                t.append(sum)
                sum = 0
            M3.append(t)
            t = []
    return M3

def     solve(L, U, B, n):
    z = [0] * n
    x = [0] * n

    z[0] = B[0]
    for i in range(1, n):
        sum = 0.0
        for j in range(i):
            sum += (L[i][j] * z[j])
        z[i] = B[i] - sum
    x[-1] = z[-1] / U[-1][-1]
    for i in reversed(range(n - 1)):
        sum = 0
        for j in range(i, n):
            sum += (U[i][j] * x[j])
        x[i] = (z[i] - sum) / U[i][i]
    return x

def     back_matrix(L, U, n):
    back = [[0] * n for i in range(n)]
    E = [[0] * n for i in range(n)]

    for i in range(n):
        E[i][i] = 1

    for i in range(n):
        back[i] = solve(L, U, E[i], n)
    back = list(zip(*back))
    return back

def     determinant(M, n, count):
    det = 1
    for i in range(n):
        det *= M[i][i]
    return det * (-1)**count

print("Input size of matrix: ")
n = int(input())
f = open('sample_1.txt', 'rt')
Matrix = []
Vector = []
i = 0

for line in f:
    Matrix.append(list(map(float, line.split())))
    Vector.append(Matrix[i][n])
    del Matrix[i][n]
    i += 1

P, L, U, count = decompose_to_LU(Matrix, n)

P = np.array(P)
Vector = np.array(Vector)
PVector = P.dot(Vector)

ans = solve(L, U, PVector, n)

back_mat = back_matrix(L, U, n)

print("----------Start matrix:----------")
for i in range(n):
    for j in range(n):
        print("%.3f" % Matrix[i][j], end=' | ')
        if j==3:
            print("\n")

print("----------L-matrix:----------")
for i in range(n):
    for j in range(n):
        print("%.3f" % L[i][j], end=' | ')
        if j==3:
            print("\n")

print("----------U-matrix:----------")
for i in range(n):
    for j in range(n):
        print("%.3f" % U[i][j], end=' | ')
        if j==3:
            print("\n")

M = matrixmult(L, U)
print("----------Result of compute L*U:----------")
for i in range(n):
    for j in range(n):
        print("%.3f" % M[i][j], end=' | ')
        if j==3:
            print("\n")

print("|A| = %.3f\n" % determinant(U, n, count))

print("----------SOLVE:----------")
for i in range(n):
    print("x_%d = %.3f\n" % ((i + 1), ans[i]))

back_mat = matrixmult(back_mat, P)

print("----------BACK MATRIX:----------")
for i in range(n):
    for j in range(n):
        print("%.3f" % back_mat[i][j], end=' | ')
        if j==3:
            print("\n")

E = matrixmult(Matrix, back_mat)

print("----------A * back matrix:----------")
for i in range(n):
    for j in range(n):
        print("%.3f" % E[i][j], end=' | ')
        if j==3:
            print("\n")


f.close()
