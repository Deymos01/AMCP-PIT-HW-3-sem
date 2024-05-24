import numpy as np

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
        self.rowExchanges = 0
        self.isLU = False
        self.rank = rows
        self.operations = 0

        if rows == cols:
            np.fill_diagonal(self.P, 1)
            np.fill_diagonal(self.Q, 1)

    def luDecomposition(self):
        if self.isLU:
            return None
        self.isLU = True

        if self.rows != self.cols:
            raise ValueError("Matrix must be square")

        # init U matrix
        self.U = self.A.copy()

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
