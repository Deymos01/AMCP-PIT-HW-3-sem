import numpy as np
from matrix import *
import time
import math

eps: float = 1e-14


class NewtonMethod:
    def __init__(self, size=10):
        self.size = size
        self.X = None
        self.F = None
        self.J = None
        self.initX()
        self.initF()
        self.initJ()

    def initX(self):
        self.X = np.array([0.5, 0.5, 1.5, -1.0, -0.5, 1.5, 0.5, -0.5, 1.5, -1.5])

    def initF(self):
        self.F = np.array([
            math.cos(self.X[0] * self.X[1]) - math.exp(-3.0 * self.X[2]) + self.X[3] * self.X[4] * self.X[4] - self.X[5] - math.sinh(2.0 * self.X[7]) * self.X[8] + 2.0 * self.X[9] + 2.0004339741653854440,
            math.sin(self.X[0] * self.X[1]) + self.X[2] * self.X[8] * self.X[6] - math.exp(-self.X[9] + self.X[5]) + 3.0 * self.X[4] * self.X[4] - self.X[5] * (self.X[7] + 1.0) + 10.886272036407019994,
            self.X[0] - self.X[1] + self.X[2] - self.X[3] + self.X[4] - self.X[5] + self.X[6] - self.X[7] + self.X[8] - self.X[9] - 3.1361904761904761904,
            2.0 * math.cos(-self.X[8] + self.X[3]) + self.X[4] / (self.X[2] + self.X[0]) - math.sin(self.X[1] * self.X[1]) + math.cos(self.X[6] * self.X[9]) * math.cos(self.X[6] * self.X[9]) - self.X[7] - 0.1707472705022304757,
            math.sin(self.X[4]) + 2.0 * self.X[7] * (self.X[2] + self.X[0]) - math.exp(-self.X[6] * (-self.X[9] + self.X[5])) + 2.0 * math.cos(self.X[1]) - 1.00 / (self.X[3] - self.X[8]) - 0.3685896273101277862,
            math.exp(self.X[0] - self.X[3] - self.X[8]) + self.X[4] * self.X[4] / self.X[7] + math.cos(3.0 * self.X[9] * self.X[1]) / 2.0 - self.X[5] * self.X[2] + 2.0491086016771875115,
            self.X[1] * self.X[1] * self.X[1] * self.X[6] - math.sin(self.X[9] / self.X[4] + self.X[7]) + (self.X[0] - self.X[5]) * math.cos(self.X[3]) + self.X[2] - 0.7380430076202798014,
            self.X[4] * (self.X[0] - 2.0 * self.X[5]) * (self.X[0] - 2.0 * self.X[5]) - 2.0 * math.sin(-self.X[8] + self.X[2]) + 1.5 * self.X[3] - math.exp(self.X[1] * self.X[6] + self.X[9]) + 3.5668321989693809040,
            7.0 / self.X[5] + math.exp(self.X[4] + self.X[3]) - 2.0 * self.X[1] * self.X[7] * self.X[9] * self.X[6] + 3.0 * self.X[8] - 3.0 * self.X[0] - 8.4394734508383257499,
            self.X[9] * self.X[0] + self.X[8] * self.X[1] - self.X[7] * self.X[2] + math.sin(self.X[3] + self.X[4] + self.X[5]) * self.X[6] - 0.78238095238095238096
        ])

    def initJ(self):
        self.J = Matrix(self.size, self.size)
        self.J.A[0, 0] = -math.sin(self.X[0] * self.X[1]) * self.X[1]
        self.J.A[0, 1] = -math.sin(self.X[0] * self.X[1]) * self.X[0]
        self.J.A[0, 2] = 3 * math.exp(-(3.0 * self.X[2]))
        self.J.A[0, 3] = self.X[4] * self.X[4]
        self.J.A[0, 4] = 2 * self.X[3] * self.X[4]
        self.J.A[0, 5] = -1
        self.J.A[0, 6] = 0
        self.J.A[0, 7] = -2 * math.cosh((2 * self.X[7])) * self.X[8]
        self.J.A[0, 8] = -math.sinh((2 * self.X[7]))
        self.J.A[0, 9] = 2
        self.J.A[1, 0] = math.cos(self.X[0] * self.X[1]) * self.X[1]
        self.J.A[1, 1] = math.cos(self.X[0] * self.X[1]) * self.X[0]
        self.J.A[1, 2] = self.X[8] * self.X[6]
        self.J.A[1, 3] = 0
        self.J.A[1, 4] = 6 * self.X[4]
        self.J.A[1, 5] = -math.exp(-self.X[9] + self.X[5]) - self.X[7] - 0.1e1
        self.J.A[1, 6] = self.X[2] * self.X[8]
        self.J.A[1, 7] = -self.X[5]
        self.J.A[1, 8] = self.X[2] * self.X[6]
        self.J.A[1, 9] = math.exp(-self.X[9] + self.X[5])
        self.J.A[2, 0] = 1
        self.J.A[2, 1] = -1
        self.J.A[2, 2] = 1
        self.J.A[2, 3] = -1
        self.J.A[2, 4] = 1
        self.J.A[2, 5] = -1
        self.J.A[2, 6] = 1
        self.J.A[2, 7] = -1
        self.J.A[2, 8] = 1
        self.J.A[2, 9] = -1
        self.J.A[3, 0] = -self.X[4] * math.pow(self.X[2] + self.X[0], -2)
        self.J.A[3, 1] = -2 * math.cos(self.X[1] * self.X[1]) * self.X[1]
        self.J.A[3, 2] = -self.X[4] * math.pow(self.X[2] + self.X[0], -2)
        self.J.A[3, 3] = -2 * math.sin(-self.X[8] + self.X[3])
        self.J.A[3, 4] = 1 / (self.X[2] + self.X[0])
        self.J.A[3, 5] = 0
        self.J.A[3, 6] = -2 * math.cos(self.X[6] * self.X[9]) * math.sin(self.X[6] * self.X[9]) * self.X[9]
        self.J.A[3, 7] = -1
        self.J.A[3, 8] = 2 * math.sin(-self.X[8] + self.X[3])
        self.J.A[3, 9] = -2 * math.cos(self.X[6] * self.X[9]) * math.sin(self.X[6] * self.X[9]) * self.X[6]
        self.J.A[4, 0] = 2 * self.X[7]
        self.J.A[4, 1] = -2 * math.sin(self.X[1])
        self.J.A[4, 2] = 2 * self.X[7]
        self.J.A[4, 3] = math.pow(-self.X[8] + self.X[3], -2)
        self.J.A[4, 4] = math.cos(self.X[4])
        self.J.A[4, 5] = self.X[6] * math.exp(-self.X[6] * (-self.X[9] + self.X[5]))
        self.J.A[4, 6] = -(self.X[9] - self.X[5]) * math.exp(-self.X[6] * (-self.X[9] + self.X[5]))
        self.J.A[4, 7] = (2 * self.X[2]) + 2 * self.X[0]
        self.J.A[4, 8] = -math.pow(-self.X[8] + self.X[3], -2)
        self.J.A[4, 9] = -self.X[6] * math.exp(-self.X[6] * (-self.X[9] + self.X[5]))
        self.J.A[5, 0] = math.exp(self.X[0] - self.X[3] - self.X[8])
        self.J.A[5, 1] = -3.0 / 2.0 * math.sin(3 * self.X[9] * self.X[1]) * self.X[9]
        self.J.A[5, 2] = -self.X[5]
        self.J.A[5, 3] = -math.exp(self.X[0] - self.X[3] - self.X[8])
        self.J.A[5, 4] = 2 * self.X[4] / self.X[7]
        self.J.A[5, 5] = -self.X[2]
        self.J.A[5, 6] = 0
        self.J.A[5, 7] = -self.X[4] * self.X[4] * math.pow(self.X[7], (-2))
        self.J.A[5, 8] = -math.exp(self.X[0] - self.X[3] - self.X[8])
        self.J.A[5, 9] = -3.0 / 2.0 * math.sin(3 * self.X[9] * self.X[1]) * self.X[1]
        self.J.A[6, 0] = math.cos(self.X[3])
        self.J.A[6, 1] = 3 * self.X[1] * self.X[1] * self.X[6]
        self.J.A[6, 2] = 1
        self.J.A[6, 3] = -(self.X[0] - self.X[5]) * math.sin(self.X[3])
        self.J.A[6, 4] = math.cos(self.X[9] / self.X[4] + self.X[7]) * self.X[9] * math.pow(self.X[4], (-2))
        self.J.A[6, 5] = -math.cos(self.X[3])
        self.J.A[6, 6] = math.pow(self.X[1], 3)
        self.J.A[6, 7] = -math.cos(self.X[9] / self.X[4] + self.X[7])
        self.J.A[6, 8] = 0
        self.J.A[6, 9] = -math.cos(self.X[9] / self.X[4] + self.X[7]) / self.X[4]
        self.J.A[7, 0] = 2 * self.X[4] * (self.X[0] - 2 * self.X[5])
        self.J.A[7, 1] = -self.X[6] * math.exp(self.X[1] * self.X[6] + self.X[9])
        self.J.A[7, 2] = -2 * math.cos(-self.X[8] + self.X[2])
        self.J.A[7, 3] = 0.15e1
        self.J.A[7, 4] = math.pow(self.X[0] - 2 * self.X[5], 2)
        self.J.A[7, 5] = -4 * self.X[4] * (self.X[0] - 2 * self.X[5])
        self.J.A[7, 6] = -self.X[1] * math.exp(self.X[1] * self.X[6] + self.X[9])
        self.J.A[7, 7] = 0
        self.J.A[7, 8] = 2 * math.cos(-self.X[8] + self.X[2])
        self.J.A[7, 9] = -math.exp(self.X[1] * self.X[6] + self.X[9])
        self.J.A[8, 0] = -3
        self.J.A[8, 1] = -2 * self.X[7] * self.X[9] * self.X[6]
        self.J.A[8, 2] = 0
        self.J.A[8, 3] = math.exp((self.X[4] + self.X[3]))
        self.J.A[8, 4] = math.exp((self.X[4] + self.X[3]))
        self.J.A[8, 5] = -0.7e1 * math.pow(self.X[5], -2)
        self.J.A[8, 6] = -2 * self.X[1] * self.X[7] * self.X[9]
        self.J.A[8, 7] = -2 * self.X[1] * self.X[9] * self.X[6]
        self.J.A[8, 8] = 3
        self.J.A[8, 9] = -2 * self.X[1] * self.X[7] * self.X[6]
        self.J.A[9, 0] = self.X[9]
        self.J.A[9, 1] = self.X[8]
        self.J.A[9, 2] = -self.X[7]
        self.J.A[9, 3] = math.cos(self.X[3] + self.X[4] + self.X[5]) * self.X[6]
        self.J.A[9, 4] = math.cos(self.X[3] + self.X[4] + self.X[5]) * self.X[6]
        self.J.A[9, 5] = math.cos(self.X[3] + self.X[4] + self.X[5]) * self.X[6]
        self.J.A[9, 6] = math.sin(self.X[3] + self.X[4] + self.X[5])
        self.J.A[9, 7] = -self.X[2]
        self.J.A[9, 8] = self.X[1]
        self.J.A[9, 9] = self.X[0]

    def classicMethod(self):
        operations = 0
        iterations = 0
        self.initX()
        start = time.time()
        while True:
            self.initF()
            self.initJ()
            if self.J.luDecomposition() is not None:
                raise ValueError("Matrix can't be LU decomposed")

            fixedF = self.J.P @ self.F
            operations += self.size

            dx = self.J.solveLU(fixedF)
            operations += self.J.operations

            for i in range(self.X.size):
                self.X[i] -= dx[i]
                operations += 1
            # print(self.X)
            if np.max(np.abs(dx)) < eps:
                break
            iterations += 1

        print("Solution: ", self.X)
        print("Iterations: ", iterations)
        print("Operations: ", operations)
        print("Time: ", time.time() - start)

    def modifiedMethod(self):
        operations = 0
        iterations = 0
        self.initX()
        self.initJ()
        start = time.time()
        if self.J.luDecomposition() is not None:
            raise ValueError("Matrix can't be LU decomposed")

        while iterations < 1000:
            self.initF()
            fixedF = self.J.P @ self.F
            operations += (self.size * self.size)

            dx = self.J.solveLU(fixedF)

            for i in range(self.X.size):
                self.X[i] -= dx[i]
                operations += 1

            if np.max(np.abs(dx)) < eps:
                break

            iterations += 1

        operations += self.J.operations
        print("Solution: ", self.X)
        print("Iterations: ", iterations)
        print("Operations: ", operations)
        print("Time: ", time.time() - start)

    def modifiedMethodWithOnlyKIterations(self, k):
        operations = 0
        iterations = 0
        self.initX()
        self.initJ()
        start = time.time()
        if self.J.luDecomposition() is not None:
            raise ValueError("Matrix can't be LU decomposed")

        while iterations < 1000:
            self.initF()

            if k >= 0:
                operations += self.J.operations
                self.initJ()
                if self.J.luDecomposition() is not None:
                    raise ValueError("Matrix can't be LU decomposed")

            fixedF = self.J.P @ self.F
            operations += (self.size * self.size)

            dx = self.J.solveLU(fixedF)
            for i in range(self.X.size):
                self.X[i] -= dx[i]
                operations += 1

            if np.max(np.abs(dx)) < eps:
                break

            k -= 1
            iterations += 1

        operations += self.J.operations
        print("Solution: ", self.X)
        print("Iterations: ", iterations)
        print("Operations: ", operations)
        print("Time: ", time.time() - start)

    def modifiedMethodWithMIterations(self, m):
        operations = 0
        iterations = 0
        self.initX()
        self.initJ()
        start = time.time()
        if self.J.luDecomposition() is not None:
            raise ValueError("Matrix can't be LU decomposed")

        while iterations < 1000:
            self.initF()

            if iterations % m == 0:
                operations += self.J.operations
                self.initJ()
                if self.J.luDecomposition() is not None:
                    raise ValueError("Matrix can't be LU decomposed")

            fixedF = self.J.P @ self.F
            operations += (self.size * self.size)

            dx = self.J.solveLU(fixedF)
            for i in range(self.X.size):
                self.X[i] -= dx[i]
                operations += 1

            if np.max(np.abs(dx)) < eps:
                break

            iterations += 1

        operations += self.J.operations
        print("Solution: ", self.X)
        print("Iterations: ", iterations)
        print("Operations: ", operations)
        print("Time: ", time.time() - start)

    def modifiedMethodTransition(self, m, k):
        operations = 0
        iterations = 0
        self.initX()
        self.initJ()
        start = time.time()

        if self.J.luDecomposition() is not None:
            raise ValueError("Matrix can't be LU decomposed")

        while iterations < 1000:
            self.initF()

            if m >= 0 or iterations % k == 0:
                operations += self.J.operations
                self.initJ()

                if self.J.luDecomposition() is not None:
                    raise ValueError("Matrix can't be LU decomposed")

            fixedF = self.J.P @ self.F
            operations += (self.size * self.size)
            dx = self.J.solveLU(fixedF)

            for i in range(self.X.size):
                self.X[i] -= dx[i]
                operations += 1

            if np.max(np.abs(dx)) < eps:
                break

            m -= 1
            iterations += 1

        operations += self.J.operations
        print("Solution: ", self.X)
        print("Iterations: ", iterations)
        print("Operations: ", operations)
        print("Time: ", time.time() - start)
