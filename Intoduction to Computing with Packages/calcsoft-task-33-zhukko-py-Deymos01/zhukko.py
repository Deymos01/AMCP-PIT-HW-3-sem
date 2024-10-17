import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp


def zhukko(a, V):
    def equations(t, y):
        x1, y1, x2, y2, x3, y3, x4, y4 = y
        dx1dt = V * (x2 - x1) / np.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)
        dy1dt = V * (y2 - y1) / np.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)
        dx2dt = V * (x3 - x2) / np.sqrt((x3 - x2) ** 2 + (y3 - y2) ** 2)
        dy2dt = V * (y3 - y2) / np.sqrt((x3 - x2) ** 2 + (y3 - y2) ** 2)
        dx3dt = V * (x4 - x3) / np.sqrt((x4 - x3) ** 2 + (y4 - y3) ** 2)
        dy3dt = V * (y4 - y3) / np.sqrt((x4 - x3) ** 2 + (y4 - y3) ** 2)
        dx4dt = V * (x1 - x4) / np.sqrt((x1 - x4) ** 2 + (y1 - y4) ** 2)
        dy4dt = V * (y1 - y4) / np.sqrt((x1 - x4) ** 2 + (y1 - y4) ** 2)
        return [dx1dt, dy1dt, dx2dt, dy2dt, dx3dt, dy3dt, dx4dt, dy4dt]

    initPos = [0, 0, a, 0, a, a, 0, a]
    tSpan = [0, 10]
    tEval = np.linspace(tSpan[0], tSpan[1], 500)

    sol = solve_ivp(equations, tSpan, initPos, t_eval=tEval)

    plt.plot(sol.y[0], sol.y[1], label='Cockroach 1')
    plt.plot(sol.y[2], sol.y[3], label='Cockroach 2')
    plt.plot(sol.y[4], sol.y[5], label='Cockroach 3')
    plt.plot(sol.y[6], sol.y[7], label='Cockroach 4')
    plt.legend()
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title("Cockroaches' trajectory")
    plt.grid()
    plt.show()
