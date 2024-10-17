import math

import numpy as np
from math import log10

eps: float = 1e-14

MIN_RANDOM = 1
MAX_RANDOM = 10


class Matrix:
    def __init__(self, rows, cols):
        self.rows, self.cols = rows, cols
        self.A = np.zeros((rows, cols), dtype=float)
        self.L = np.zeros((rows, cols), dtype=float)
        self.U = np.zeros((rows, cols), dtype=float)
        self.P = np.zeros((rows, cols), dtype=float)
        self.Q = np.zeros((rows, cols), dtype=float)
        self.R = np.zeros((rows, cols), dtype=float)
        self.rowExchanges = 0
        self.isLU = False
        self.isQR = False
        self.rank = rows
        self.operations = 0

        if rows == cols:
            np.fill_diagonal(self.P, 1)
            np.fill_diagonal(self.Q, 1)

    def initSampleA(self):
        self.__init__(self.rows, self.cols)
        self.A = np.array([[2, 9, 7, 4, 8],
                           [7, 3, 5, 1, 10],
                           [8, 6, 3, 10, 8],
                           [10, 7, 7, 1, 5],
                           [2, 2, 9, 4, 10]], dtype=float)
        if self.rows == self.cols:
            self.R = self.A.copy()

    def initRandomA(self):
        self.__init__(self.rows, self.cols)
        # init matrix A with random integers
        self.A = np.random.randint(MIN_RANDOM, MAX_RANDOM + 1, (self.rows, self.cols)).astype(float)
        if self.rows == self.cols:
            self.R = self.A.copy()

    def initDiagonalDominantSampleA(self):
        self.__init__(self.rows, self.cols)
        self.A = np.random.randint(MIN_RANDOM, MAX_RANDOM + 1, (self.rows, self.cols)).astype(float)
        for i in range(self.rows):
            s = 0.0
            for j in range(self.cols):
                s += abs(self.A[i, j])
            self.A[i, i] = s + 1

        if self.rows == self.cols:
            self.R = self.A.copy()

    def initDiagonalDominantRandomA(self):
        self.__init__(self.rows, self.cols)
        self.A = np.array([[2, 9, 7, 4, 8],
                           [7, 3, 5, 1, 10],
                           [8, 6, 3, 10, 8],
                           [10, 7, 7, 1, 5],
                           [2, 2, 9, 4, 10]], dtype=float)
        for i in range(self.rows):
            s = 0.0
            for j in range(self.cols):
                s += abs(self.A[i, j])
            self.A[i, i] = s + 1

        if self.rows == self.cols:
            self.R = self.A.copy()

    # task 1
    def luDecomposition(self):
        if self.isLU:
            return None
        self.isLU = True

        if self.rows != self.cols:
            raise ValueError("Matrix must be square")

        # init U matrix
        self.U = self.A.copy()

# TODO: заменить на while
        for i in range(self.rows):
            if abs(self.U[i, i]) < eps:  # if diagonal element is zero then swap
                for j in range(i + 1, self.rows):
                    if abs(self.U[j, i]) > eps:
                        self.U[[i, j]] = self.U[[j, i]]
                        self.L[[i, j]] = self.L[[j, i]]
                        self.P[[i, j]] = self.P[[j, i]]
                        self.rowExchanges += 1
                        break

                if i >= self.rank:
                    break
                if 0 <= i < self.rank - 1:
                    self.U[:, [i, self.rank - 1]] = self.U[:, [self.rank - 1, i]]
                    self.Q[:, [i, self.rank - 1]] = self.Q[:, [self.rank - 1, i]]

                self.rank -= 1
                if i >= 0:
                    i -= 1
                continue

            max = abs(self.U[i, i])
            pivot = i
            # Choose maximum element in column i
            for j in range(i + 1, self.rows):
                if abs(self.U[j, i]) > max and self.U[j, i] != 0:
                    max = abs(self.U[j, i])
                    pivot = j

            if pivot != i:  # if pivot is not equal to i then swap
                self.U[[i, pivot]] = self.U[[pivot, i]]
                self.L[[i, pivot]] = self.L[[pivot, i]]
                self.P[[i, pivot]] = self.P[[pivot, i]]
                self.rowExchanges += 1

            # Gaussian elimination
            for k in range(i + 1, self.rows):
                if abs(self.U[i, i]) > eps:
                    coef = self.U[k, i] / self.U[i, i]
                    self.operations += 1
                    if abs(coef) < eps:
                        continue
                    for j in range(i, self.cols):
                        self.U[k, j] -= coef * self.U[i, j]
                        self.operations += 1
                    self.L[k, i] = coef

        np.fill_diagonal(self.L, 1)

        return None

    def determinant(self):
        if self.rows != self.cols:
            raise ValueError("Matrix must be square")

        if self.luDecomposition() is not None:
            raise ValueError("Matrix can't be LU decomposed")

        det = 1.0
        for i in range(self.rows):
            det *= self.U[i, i]

        return det if self.rowExchanges % 2 == 0 else -det

    def inverse(self):
        if self.luDecomposition() is not None:
            raise ValueError("Matrix can't be LU decomposed")

        res = np.zeros((self.rows, self.cols), dtype=float)
        for i in range(self.rows):
            y = np.zeros(self.rows, dtype=float)
            for j in range(self.rows):
                y[j] = self.P[j, i]
                self.operations += 1

            x = self.solveLU(y)
            for j in range(self.rows):
                res[j, i] = x[j]
                self.operations += 1
        return res

    def conditionNumber(self):
        if self.luDecomposition() is not None:
            raise ValueError("Matrix can't be LU decomposed")

        invA = self.inverse()
        return np.linalg.norm(invA, ord=1) * np.linalg.norm(self.A, ord=1)

    # task 2
    def solveLU(self, B):
        if self.luDecomposition() is not None:
            raise ValueError("Matrix can't be LU decomposed")

        y = np.zeros(self.rows, dtype=float)
        for i in range(self.rows):
            y[i] = B[i]
            for j in range(i):
                y[i] -= self.L[i, j] * y[j]
                self.operations += 1

        x = np.zeros(self.rows, dtype=float)
        for i in range(self.rows - 1, -1, -1):
            if i > self.rank - 1 and abs(self.U[i, i] - y[i]) > eps:
                raise ValueError("System is inconsistent")
            else:
                x[i] = y[i]
                for j in range(i + 1, self.cols):
                    x[i] -= self.U[i, j] * x[j]
                    self.operations += 1
                x[i] /= self.U[i, i]
                self.operations += 1

        res = self.Q @ x
        self.operations += self.rows * self.cols
        return res

    # task 3
    def qrDecomposition(self):
        if self.isQR:
            return None
        self.isQR = True

        self.Q = np.eye(self.rows)
        G = np.eye(self.rows)

        for j in range(self.cols):
            for i in range(self.rows - 1, j, -1):
                if abs(self.R[i, j]) < eps:
                    continue

                # calculate Givens rotation matrix
                cosVal = self.R[j, j] / np.sqrt(self.R[j, j] ** 2 + self.R[i, j] ** 2)
                sinVal = self.R[i, j] / np.sqrt(self.R[j, j] ** 2 + self.R[i, j] ** 2)

                # apply Givens rotation matrix
                G[j, j], G[i, i] = cosVal, cosVal
                G[i, j], G[j, i] = -sinVal, sinVal

                self.Q = G @ self.Q
                self.R = G @ self.R

                G[j, j], G[i, i] = 1, 1
                G[i, j], G[j, i] = 0, 0

        self.Q = self.Q.T
        return None

    def solveQR(self, B):
        if self.qrDecomposition() is not None:
            raise ValueError("Matrix is not QR decomposed")

        qB = self.Q.T @ B
        x = np.zeros(self.cols, dtype=float)
        for i in range(self.rows - 1, -1, -1):
            x[i] = qB[i]
            for j in range(i + 1, self.cols):
                x[i] -= self.R[i, j] * x[j]
            x[i] /= self.R[i, i]
        return x

    @staticmethod
    def getBc(matrix, b):
        n = len(matrix)
        l = np.zeros((n, n))
        invD = np.zeros((n, n))
        r = np.zeros((n, n))

        for i in range(n):
            invD[i, i] = 1 / matrix[i, i]
            for j in range(i):
                l[i, j] = matrix[i, j]
            for j in range(i + 1, n):
                r[i, j] = matrix[i, j]

        B = np.negative(invD @ (l + r))
        c = invD @ b
        return B, c

    def jacobi(self, b):
        B, c = self.getBc(self.A, b)
        prevX = np.copy(c)
        Bx = B @ prevX
        x = Bx + c

        q = np.linalg.norm(B, ord=1)
        cond = 0.01 if q > 1 else (1 - q) / q
        iters = 0
        priori = math.floor(abs((log10(eps) - log10(np.linalg.norm(c)) + log10(abs(1 - q))) / log10(q)))

        while np.linalg.norm(x - prevX) > cond * eps * np.linalg.norm(self.A, ord=1):
            if iters > 1000:
                raise ValueError("Method does not converge")
            prevX = np.copy(x)
            Bx = B @ x
            x = Bx + c
            iters += 1

        aposter = iters
        return x, aposter, priori

    def seidel(self, b):
        B, c = self.getBc(self.A, b)
        prevX = np.copy(c)
        Bx = B @ prevX
        x = Bx + c

        q = np.linalg.norm(B, ord=1)
        cond = 0.01 if q > 1 else (1 - q) / q
        iters = 0
        priori = math.floor(abs((log10(eps) - log10(np.linalg.norm(c)) + log10(abs(1 - q))) / log10(q)))

        while np.linalg.norm(x - prevX) > cond * eps * np.linalg.norm(self.A, ord=1):
            if iters > 10000:
                raise ValueError("Method does not converge")

            prevX = np.copy(x)
            for i in range(self.rows):
                tmp = c[i]
                for j in range(self.cols):
                    tmp += B[i, j] * x[j]
                x[i] = tmp
            iters += 1

        aposter = iters
        return x, aposter, priori