import math
from math import cos, exp, sin, pow, log
import numpy as np

# Integral #14
eps: float = 1e-6
a: float = 2.3
b: float = 2.9
alpha: float = 0
beta: float = 2 / 5
exactSolution: float = 348.8181344253911360363589124705960119778
methodicalError: float = 7.682110675943062


def f(x: float) -> float:
    return 3 * cos(2.5 * x) * exp(7 * x / 4) + 5 * sin(0.5 * x) * exp(3 * x / 8) + 4


def getMoments(start: float, end: float) -> np.array:
    moments = np.zeros((6, 1), dtype=float)
    moments[0, 0] = 5 / 3 * (pow(abs(b - start), 3 / 5) - pow(abs(b - end), 3 / 5))
    moments[1, 0] = 5 / 24 * (pow(abs(b - start), 3 / 5) * (3 * start + 5 * b) - pow(abs(b - end), 3 / 5) * (3 * end + 5 * b))
    moments[2, 0] = 5 / 156 * (pow(abs(b - start), 3 / 5) * (12 * start ** 2 + 15 * b * start + 25 * b ** 2) - pow(abs(b - end), 3 / 5) * (12 * end ** 2 + 15 * b * end + 25 * b ** 2))
    moments[3, 0] = 5 / 936 * (pow(abs(b - start), 3 / 5) * (52 * start ** 3 + 60 * b * start ** 2 + 75 * b ** 2 * start + 125 * b ** 3) - pow(abs(b - end), 3 / 5) * (52 * end ** 3 + 60 * b * end ** 2 + 75 * b ** 2 * end + 125 * b ** 3))
    moments[4, 0] = 5 / 5382 * (pow(abs(b - start), 3 / 5) * (234 * start ** 4 + 260 * b * start ** 3 + 300 * b ** 2 * start ** 2 + 375 * b ** 3 * start + 625 * b ** 4) - pow(abs(b - end), 3 / 5) * (234 * end ** 4 + 260 * b * end ** 3 + 300 * b ** 2 * end ** 2 + 375 * b ** 3 * end + 625 * b ** 4))
    moments[5, 0] = 5 / 150696 * (pow(abs(b - start), 3 / 5) * (5382 * start ** 5 + 5850 * b * start ** 4 + 6500 * b ** 2 * start ** 3 + 7500 * b ** 3 * start ** 2 + 9375 * b ** 4 * start + 15625 * b ** 5) - pow(abs(b - end), 3 / 5) * (5382 * end ** 5 + 5850 * b * end ** 4 + 6500 * b ** 2 * end ** 3 + 7500 * b ** 3 * end ** 2 + 9375 * b ** 4 * end + 15625 * b ** 5))
    return moments


def newtonCotes(steps: int) -> float:
    step: float = abs(b - a) / steps
    x1: float = a
    x2: float = a + step / 2
    x3: float = a + step
    ans: float = 0.0

    for i in range(steps):
        moments: np.array = getMoments(x1, x3)[0:3]

        coef: np.array = np.array([
            [1, 1, 1],
            [x1, x2, x3],
            [x1 ** 2, x2 ** 2, x3 ** 2]
        ], dtype=float)
        sol: np.array = np.linalg.solve(coef, moments)
        ans += sol[0, 0] * f(x1) + sol[1, 0] * f(x2) + sol[2, 0] * f(x3)

        x1 += step
        x2 += step
        x3 += step

    return ans


def dynamicStep_SQF(steps: int, method) -> float:
    ans1: float = method(steps)
    steps *= 2
    ans2: float = method(steps)
    res: float = ans2

    err: float = abs(ans2 - ans1)
    iterations: int = 1
    while err > eps:
        steps *= 2
        ans3: float = method(steps)
        res = ans3

        speed: float = -log(abs((ans3 - ans2) / (ans2 - ans1))) / log(2)
        err = abs((ans3 - ans2) / (pow(2, speed) - 1))

        print(f"Iteration #{iterations}")
        print(f"Steps: {steps}")
        print(f"Speed: {speed}")
        print(f"Error: {err}")
        print(f"Exact error: {res - exactSolution}\n")

        ans1, ans2 = ans2, ans3
        iterations += 1

    return res


def gauss(steps: int) -> float:
    ans: float = 0
    step: float = abs((b - a) / steps)
    start: float = a
    end: float = a + step

    for i in range(steps):
        moments: np.array = getMoments(start, end)

        vecB: np.array = moments[3:]
        coef: np.array = np.array([
            moments[0:3, 0],
            moments[1:4, 0],
            moments[2:5, 0]
        ])

        A: np.array = np.linalg.solve(coef, -vecB)
        polyCoef: np.array = np.array([1, A[2, 0], A[1, 0], A[0, 0]], dtype=float)
        x: np.array = np.roots(polyCoef)

        coef: np.array = np.array([
            [1, 1, 1],
            [x[0], x[1], x[2]],
            [x[0] ** 2, x[1] ** 2, x[2] ** 2]
        ])

        sol: np.array = np.linalg.solve(coef, moments[0:3, 0])
        ans += sol[0] * f(x[0]) + sol[1] * f(x[1]) + sol[2] * f(x[2])

        start += step
        end += step

    return ans


def main():
    # task 1
    print("======NewtonCotes======")
    ans: float = newtonCotes(2)
    print(f"Answer: {ans}")
    print(f"Expected: {exactSolution}")
    print(f"Mistake: {abs(exactSolution - ans)}")
    print(f"Methodical Error: {methodicalError}")
    print("==========END==========\n\n\n")

    # task 2
    print("======NewtonCotes dynamic step======")
    steps: int = 1
    ans = dynamicStep_SQF(steps, newtonCotes)
    print("==========")
    print(f"Answer: {ans}")
    print(f"Expected: {exactSolution}")
    print(f"Mistake: {abs(ans - exactSolution)}")
    print("==========END==========\n\n\n")

    # task 3
    print("======NewtonCotes hOptimal======")
    ans1: float = newtonCotes(1)
    ans2: float = newtonCotes(2)
    ans3: float = newtonCotes(4)

    speed: float = -log(abs((ans3 - ans2) / (ans2 - ans1))) / log(2)
    err: float = (ans3 - ans2) / (pow(2, speed) - 1)

    print(f"Speed t3: {speed}")
    print(f"Error t3: {err}")
    print(f"t3: {pow(abs(eps / err), 1 / speed)}")

    hOpt: int = int(math.ceil(4 / pow(abs(eps / err), 1 / speed)))
    ans = dynamicStep_SQF(hOpt, newtonCotes)
    print("==========")
    print(f"Answer: {ans}")
    print(f"Expected: {exactSolution}")
    print(f"Mistake: {abs(ans - exactSolution)}")
    print(f"hOptimal: {hOpt}")
    print("==========END==========\n\n\n")

    # task 4
    print("======Gauss======")
    ans = gauss(2)
    print(f"Answer: {ans}")
    print(f"Expected: {exactSolution}")
    print(f"Mistake: {abs(ans - exactSolution)}")
    print("==========END==========\n\n\n")

    print("======Gauss Dynamic Step======")
    steps: int = 1
    ans = dynamicStep_SQF(steps, gauss)
    print(f"Answer: {ans}")
    print(f"Expected: {exactSolution}")
    print(f"Mistake: {abs(ans - exactSolution)}")
    print("==========END==========\n\n\n")

    print("======Gauss hOptimal======")
    ans1: float = gauss(1)
    ans2: float = gauss(2)
    ans3: float = gauss(4)

    speed: float = -log(abs((ans3 - ans2) / (ans2 - ans1))) / log(2)
    err: float = (ans3 - ans2) / (pow(2, speed) - 1)

    hOpt: int = int(math.ceil(4 / pow(eps / err, 1 / speed)))
    ans = dynamicStep_SQF(hOpt, gauss)
    print(f"Answer: {ans}")
    print(f"Expected: {exactSolution}")
    print(f"Mistake: {abs(ans - exactSolution)}")
    print(f"hOptimal: {hOpt}")
    print("==========END==========\n\n\n")


if __name__ == '__main__':
    main()
