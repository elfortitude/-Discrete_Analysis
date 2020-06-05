import copy

def mult_matrix(M1, M2):
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
    return(M3)

def pivot_matrix(M):
    """Returns the pivoting matrix for M, used in Doolittle's method."""
    m = len(M)

    # Create an identity matrix, with floating point values
    id_mat = [[float(i ==j) for i in range(m)] for j in range(m)]

    # Rearrange the identity matrix such that the largest element of
    # each column of M is placed on the diagonal of of M
    for j in range(m):
        row = max(range(j, m), key=lambda i: abs(M[i][j]))
        if j != row:
            # Swap the rows
            id_mat[j], id_mat[row] = id_mat[row], id_mat[j]
    return id_mat

def lu_decomposition(A, n):
    """Performs an LU Decomposition of A (which must be square)
    into PA = LU. The function returns P, L and U."""
    #n = len(A)

    # Create zero matrices for L and U
    L = [[0.0] * n for i in range(n)]
    U = [[0.0] * n for i in range(n)]
    #PA = [[0.0] * n for i in range(n)]
    # Create the pivot matrix P and the multipled matrix PA
    P = pivot_matrix(A)
    #print(P)
    PA = mult_matrix(P, A)
    #print(PA)

    # Perform the LU Decomposition
    for j in range(n):
        # All diagonal entries of L are set to unity
        L[j][j] = 1.0

        # LaTeX: u_{ij} = a_{ij} - \sum_{k=1}^{i-1} u_{kj} l_{ik}
        for i in range(j+1):
            s1 = sum(U[k][j] * L[i][k] for k in range(i))
            U[i][j] = PA[i][j] - s1

        # LaTeX: l_{ij} = \frac{1}{u_{jj}} (a_{ij} - \sum_{k=1}^{j-1} u_{kj} l_{ik} )
        for i in range(j, n):
            s2 = sum(U[k][j] * L[i][k] for k in range(j))
            L[i][j] = (PA[i][j] - s2) / U[j][j]

    return (P, L, U)

def     determinant(M, n):
    det = 1
    for i in range(n):
        det *= M[i][i]
    return det

print("Input size of matrix: ")
n = int(input())
f = open('sample_1.txt', 'rt')
Matrix = []
Vector = []
M = [[0] * n for i in range(n)]
back_mat = [[0] * n for i in range(n)]
ans = []
L =[]
U = []
i = 0

for line in f:
    Matrix.append(list(map(float, line.split())))
    Vector.append(Matrix[i][n])
    del Matrix[i][n]
    i += 1

P, L, U = lu_decomposition(Matrix, n)

Matrix = mult_matrix(P, Matrix)

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

M = mult_matrix(L, U)
#M = mult_matrix(P, M)
print("----------Result of compute L*U:----------")
for i in range(n):
    for j in range(n):
        print("%.3f" % M[i][j], end=' | ')
        if j==3:
            print("\n")

print("|A| = %.3f\n" % determinant(U, n))
