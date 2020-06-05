import copy
import math
import numpy as np


def decompose_to_ab(Matrix, Vector, n):
    alpha = []
    beta = []
    P, count = pivot_matrix(Matrix)
    PMatrix = matmult(P, Matrix)
    PVector = vectmult(P, Vector)
    for i in range(n):
        alpha.append([])
        b = PVector[i] / PMatrix[i][i]
        beta.append(b)
        for j in range(n):
            if i == j:
               alpha[i].append(0)
            else:
                a = (-1) * PMatrix[i][j] / PMatrix[i][i]
                alpha[i].append(a)
    return alpha, beta, P


def pivot_matrix(M):
    m = len(M)
    count = 0
    id_mat = [[float(i == j) for i in range(m)] for j in range(m)]
    for j in range(m):
        row = max(range(j, m), key=lambda i: abs(M[i][j]))
        if j != row:
            count += 1
            id_mat[j], id_mat[row] = id_mat[row], id_mat[j]
    return id_mat, count


def matmult(m1,m2):
    r=[]
    m=[]
    if len(m1[0]) != len(m2):
        print('error')
        exit(1)
    for i in range(len(m1)):
        for j in range(len(m2[0])):
            sums=0
            for k in range(len(m2)):
                sums += (m1[i][k]*m2[k][j])
            r.append(sums)
        m.append(r)
        r=[]
    return m

def vectmult(m, v):
    r = []
    if len(m[0]) != len(v):
        print('error')
        exit(1)
    for i in range(len(m)):
        sums = 0
        for j in range(len(v)):
            sums += m[i][j] * v[j]
        r.append(sums)
    return r


def norm_c(a, n):
    max_sum = 0
    for i in range(n):
        sum = 0
        for j in range(n):
            sum += abs(a[i][j])
        if sum > max_sum:
            max_sum = sum
    return max_sum

def vect_norm_c(b, n):
    max = 0
    for j in range(n):
        if abs(b[j]) > max:
            max = abs(b[j])
    return max


def difference_vect(v1, v2):
    v3 = []
    if len(v1) != len(v2):
        print('error')
        exit(1)
    for i in range(len(v1)):
        v3.append(v1[i] - v2[i])
    return v3


def addition_vect(v1, v2):
    v3 = []
    if len(v1) != len(v2):
        print('error')
        exit(1)
    for i in range(len(v1)):
        v3.append(v1[i] + v2[i])
    return v3


def iteration(alpha, beta, eps, norm_alpha, n):
    X = []
    Eps = []
    X.append(beta)
    Eps.append(eps)
    check = 1
    i = 1
    while check > eps:
        x = addition_vect(beta, vectmult(alpha, X[i-1]))
        X.append(x)
        if norm_alpha < 1:
            check = (norm_alpha / (1 - norm_alpha)) * (vect_norm_c(difference_vect(X[i], X[i-1]), n))
        else:
            check = vect_norm_c(difference_vect(X[i], X[i-1]), n)
        Eps.append(check)
        i += 1
    return X, i-1, Eps


def estimate(eps, norm_beta, norm_alpha):
    answer = (math.log10(eps) - math.log10(norm_beta) + math.log10(1 - norm_alpha)) / math.log10(norm_alpha)
    return answer

def identity_matrix(M, n):
    E = []
    for i in range(n):
        E.append([])
        for j in range(n):
            if i == j:
                E[i].append(1)
            else:
                E[i].append(0)
    return E


def decompose_to_bc(alpha, n):
    B = []
    C = []
    for i in range(n):
        B.append([])
        C.append([])
        for j in range(n):
            if i > j:
                B[i].append(alpha[i][j])
                C[i].append(0)
            else:
                B[i].append(0)
                C[i].append(alpha[i][j])
    return B, C


def zeydel(beta, E, B, C, eps, norm_alpha, n):
    X = []
    Eps = []
    X.append(beta)
    Eps.append(eps)
    E = np.array(E)
    B = np.array(B)
    a = matmult(np.linalg.inv(difference_vect(E, B)), C)
    b = vectmult(np.linalg.inv(difference_vect(E, B)), beta)
    normC = norm_c(C, n)
    check = 1
    i = 1
    while check > eps:
        x = addition_vect(vectmult(a, X[i-1]), b)
        X.append(x)
        if norm_alpha < 1:
            check = (normC / (1 - norm_alpha)) * vect_norm_c(difference_vect(X[i], X[i-1]), n)
        else:
            check = vect_norm_c(difference_vect(X[i], X[i-1]), n)
        Eps.append(check)
        i += 1
    return X, i-1, Eps


print("Input size of matrix: ")
n = int(input())
print("Input initial approximation(epsilon):")
eps = float(input())
f = open('sample_3.txt', 'rt')
Matrix = []
Vector = []
X = []
i = 0

for line in f:
    Matrix.append(list(map(float, line.split())))
    Vector.append(Matrix[i][n])
    del Matrix[i][n]
    i += 1

alpha, beta, P = decompose_to_ab(Matrix, Vector, n)
norm_alpha = norm_c(alpha, n)
norm_beta = vect_norm_c(beta, n)
X, count, Eps = iteration(alpha, beta, eps, norm_alpha, n)
iter_count = estimate(eps, norm_beta, norm_alpha)
E = identity_matrix(alpha, n)
B, C = decompose_to_bc(alpha, n)
X_Zeydel, count_Zeydel, Eps_Zeydel = zeydel(beta, E, B, C,eps, norm_alpha, n)

print("----------Start matrix:----------")
for i in range(n):
    for j in range(n):
        print("%.3f" % Matrix[i][j], end=' | ')
    print("%.3f\n" % Vector[i])

print("----------Alpha matrix:----------")
for i in range(n):
    for j in range(n):
        print("%.3f" % alpha[i][j], end=' | ')
        if j==(n-1):
            print("\n")

print("----------Beta vector:----------")
for i in range(n):
    print("%.3f" % beta[i])
print("\n", end="")

print("----------Проверка достаточного условия сходимости:----------")
print("norm(alpha) = %.3f < 1" % norm_alpha)
if norm_alpha < 1:
    print("\tВЫПОЛНЕНО\n")
else:
    print("\tНЕ ВЫПОЛНЕНО\n")

print("----------Iteration process:----------")
for i in range(count + 1):
    print("x(%d) = ( " % i, end="")
    for j in range(n):
        print("%.3f " % X[i][j], end="")
    print("), eps(%d) = %.3f\n" % (i, Eps[i]))

print("----------Answer:----------")
for i in range(n):
    print("x%d = %.2f" % (i, X[count][i]))
print("\n", end="")

print("----------Априорная оценка необходимого кол-ва итераций:----------")
print("k+1 >= %.3f\n" % iter_count)

print("----------Zeydel process:----------")
for k in range(count_Zeydel + 1):
    for i in range(n):
        print("x(%d)_%d = %.3f\n" % (k, i, X_Zeydel[k][i]))
    print("\n", end="")

print("----------Answer:----------")
for i in range(n):
    print("x%d = %.2f" % (i, X_Zeydel[count_Zeydel][i]))
print("\n", end="")
