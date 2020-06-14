import copy
import math
import numpy as np

def complex(now, last, last_plus1):
    c1 = []
    c2 = []
    c1.append(now[0][0] - last[0])
    c1.append(now[0][1] - last[1])
    c2.append(now[1][0] - last_plus1[0])
    c2.append(now[1][1] - last_plus1[1])
    return max(math.sqrt(c1[0] ** 2 + c1[1] ** 2), math.sqrt(c2[0] ** 2 + c2[1] ** 2))


def equal(a, b, c):
    ans = []
    D = b * b - 4 * a * c
    if D >= 0:
        ans.append([])
        tmp = (-b + math.sqrt(D)) / (2 * a)
        ans[0].append(tmp)
        ans[0].append(0)
        ans.append([])
        tmp = (-b - math.sqrt(D)) / (2 * a)
        ans[1].append(tmp)
        ans[1].append(0)
    else:
        ans.append([])
        tmp = -b / (2 * a)
        ans[0].append(tmp)
        tmp = math.sqrt(-D) / (2 * a)
        ans[0].append(tmp)
        ans.append([])
        tmp = -b / (2 * a)
        ans[1].append(tmp)
        tmp = -math.sqrt(-D) / (2 * a)
        ans[1].append(tmp)
    return ans


def transpose_mat(mat, n):
    t = []
    for i in range(n):
        t.append([])
        for j in range(n):
            t[i].append(mat[j][i])
    return t


def round_mat(mat, n):
    for i in range(n):
        for j in range(n):
            mat[i][j] = float('{:.5f}'.format(mat[i][j]))
    return mat


def difference_mats(mat1, mat2):
    res = []
    if len(mat1) != len(mat2):
        print('error')
        exit(1)
    for i in range(len(mat1)):
        res.append([])
        for j in range(len(mat2)):
            res[i].append(mat1[i][j] - mat2[i][j])
    return res


def num_mat_mult(num, mat):
    for i in range(len(mat)):
        for j in range(len(mat)):
            mat[i][j] = num * mat[i][j]
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


def transpose(vect, n):
    t = []
    for i in range(n):
        t.append(vect[i][0])
    return t


def sign_f(n):
    if n == 0:
        return 0
    elif n > 0:
        return 1
    else:
        return -1


def vectmult(v1, v2):
    res = []
    sums = 0
    if type(v1[0]) == list:
        for i in range(len(v1)):
            res.append([])
            for j in range(len(v2)):
                sums = v1[i][0] * v2[j]
                res[i].append(sums)
        return res
    else:
        for i in range(len(v1)):
            sums += v1[i] * v2[i][0]
        return sums


def identity_matrix(n):
    E = []
    for i in range(n):
        E.append([])
        for j in range(n):
            if i == j:
                E[i].append(1)
            else:
                E[i].append(0)
    return E


def decompose_to_QR(m, n):
    A = []
    H = []
    Q = []
    R = []
    v = []
    E = identity_matrix(n)
    A.append(m)
    for i in range(1, n):
        v.append([])
        sum = 0
        for j in range(n):
            if i-1 > j:
                v[i-1].append([0])
            elif i-1 == j:
                for k in range(j, n):
                    sum += A[i-1][k][j] ** 2
                tmp = A[i-1][i-1][j] + sign_f(A[i-1][j][j]) * (sum ** (1/2))
                v[i-1].append([tmp])
            else:
                v[i-1].append([A[i-1][j][i-1]])
        h = difference_mats(E, num_mat_mult(2 / vectmult(transpose(v[i-1], n), v[i-1]), vectmult(v[i-1], transpose(v[i-1], n))))
        H.append(h)
        A.append(matmult(H[i-1], A[i-1]))
        A[i] = round_mat(A[i], n)
    R = A[n-1]
    Q = H[0]
    for i in range(1, len(H)):
        Q = matmult(Q, H[i])
    Q = round_mat(Q, n)
    return Q, R


def solve(m, eps, n):
    A = []
    x = []
    for i in range(n):
        x.append([])
        x[i].append(0)
        x[i].append(0)
    A.append(m)
    check = True
    count = 1
    while check:
        Q, R = decompose_to_QR(A[count-1], n)
        A.append(matmult(R, Q))
        check = False
        j = 0
        while j < n:
            sum = 0
            for i in range(j+1, n):
                sum += (A[count][i][j]) ** 2
            sum = sum ** (1/2)
            if sum > eps:
                tmp = equal(1, -A[count][j][j]-A[count][j+1][j+1], A[count][j][j]*A[count][j+1][j+1]-A[count][j][j+1]*A[count][j+1][j])
                if (complex(tmp, x[j], x[j+1]) > eps):
                    check = True
                x[j] = tmp[0]
                x[j+1] = tmp[1]
                if (tmp[0][0] == tmp[1][0] and tmp[0][1] == -tmp[1][1]):
                    j += 1
            else:
                x[j][0] = A[count][j][j]
                x[j][1] = 0
            j += 1
        count += 1
    return x, A[count-2], count-2


print("Input size of matrix: ")
n = int(input())
print("Input initial approximation(epsilon):")
eps = float(input())
f = open('sample_5.txt', 'rt')
Matrix = []

for line in f:
    Matrix.append(list(map(float, line.split())))

ans, A, count = solve(Matrix, eps, n)

print('\n', end='')
print("----------Start matrix:----------")
for i in range(n):
    for j in range(n):
        print("%.3f" % Matrix[i][j], end=' | ')
        if j==(n-1):
            print("\n")

print("----------Eigenvalues:----------")
i = 0
while i < n:
    if ans[i][1] == 0:
        print('lambda_%d = %.2f' % (i, ans[i][0]))
        i += 1
    else:
        print('lambda_%d = %.2f' % (i, ans[i][0]), end='')
        if ans[i][1] > 0:
            print(' + %.2f' % ans[i][1])
        else:
            print(' - %.2f' % (ans[i][1] * (-1)))
        i += 1
print('\n', end='')

print(ans)

print("----------Iterations:----------")
print('%d\n' % count)


