import copy
import math
import numpy as np


def eigenvector(mat, n):
    r = len(mat)
    X = mat[0]
    for i in range(1, r):
        X = matmult(X, mat[i])
        # X = round_mat(X, n)
    return (X)


def check(mat, n):
    sum = 0
    for i in range(n):
        for j in range(n):
            if i < j:
                sum += mat[i][j] ** 2
    return sum ** (1/2)


def round_mat(mat, n):
    for i in range(n):
        for j in range(n):
            mat[i][j] = float('{:.2f}'.format(mat[i][j]))
    return mat


def matmult(m1, m2):
    r = []
    m = []
    if len(m1[0]) != len(m2):
        print('error')
        exit(1)
    for i in range(len(m1)):
        for j in range(len(m2[0])):
            sums = 0
            for k in range(len(m2)):
                sums += (m1[i][k]*m2[k][j])
            r.append(sums)
        m.append(r)
        r = []
    return m


def transpose(mat, n):
    t = []
    for i in range(n):
        t.append([])
        for j in range(n):
            t[i].append(mat[j][i])
    return t


def rotation_mat(mat, i, j, n):
    U = []
    if mat[i][i] == mat[j][j]:
        phi = math.pi / 4
    else:
        phi = 0.5 * math.atan(2 * mat[i][j] / (mat[i][i] - mat[j][j]))
    for l in range(n):
        U.append([])
        for m in range(n):
            if l == i and m == i:
                U[l].append(math.cos(phi))
            elif l == i and m == j:
                U[l].append((-1) * math.sin(phi))
            elif l == j and m == i:
                U[l].append(math.sin(phi))
            elif l == j and m == j:
                U[l].append(math.cos(phi))
            elif l == m:
                U[l].append(1)
            else:
                U[l].append(0)
    return U


def max_elem(mat, n):
    max_mat = 0
    i_save = 0
    j_save = 0
    for i in range(n):
        for j in range(n):
            if i < j  and abs(mat[i][j]) > max_mat:
                max_mat = abs(mat[i][j])
                i_save = i
                j_save = j
    return max_mat, i_save, j_save


def solve(mat, eps, n):
    lam = []
    U = []
    A = []
    Eps = []
    t = 1
    i = 1
    A.append(mat)
    Eps.append(eps)
    while t > eps:
        max_mat, i_max, j_max = max_elem(A[i-1], n)
        U.append(rotation_mat(A[i-1], i_max, j_max, n))
        # U[i-1] = round_mat(U[i-1], n)
        A.append(matmult(matmult(transpose(U[i-1], n), A[i-1]), U[i-1]))
        # A[i] = round_mat(A[i], n)
        t = check(A[i], n)
        if t == Eps[i-1]:
            break
        Eps.append(t)
        i += 1
    for l in range(n):
        for m in range(n):
            if l == m:
                lam.append(A[i-1][l][m])
    return lam, U, i-1

print("Input size of matrix: ")
n = int(input())
print("Input initial approximation(epsilon):")
eps = float(input())
f = open('sample_4.txt', 'rt')
Matrix = []

for line in f:
    Matrix.append(list(map(float, line.split())))

for i in range(n):
    for j in range(n):
        if i != j and Matrix[i][j] != Matrix[j][i]:
            print('Ошибка! Матрица не является симметричной.')

lam, U, count = solve(Matrix, eps, n)
X = eigenvector(U, n)

print('\n', end='')
print("----------Start matrix:----------")
for i in range(n):
    for j in range(n):
        print("%.3f" % Matrix[i][j], end=' | ')
        if j==(n-1):
            print("\n")

print("----------Eigenvalues:----------")
for i in range(n):
    print('lambda_%d = %.3f' % (i, lam[i]))
print('\n', end='')

print("----------Iterations:----------")
print('%d\n' % count)

print("----------Eigenvector:----------")
for j in range(n):
    print('x(%d) = (' % j, end='')
    for i in range(n):
        print(' %.3f ' % X[i][j], end='')
    print(')\n')