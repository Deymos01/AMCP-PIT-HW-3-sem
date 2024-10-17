import numpy as np
import matplotlib.pyplot as plt


def madcoc(startCoords, a, phi, V):
    x0, y0, z0 = startCoords
    r0 = np.sqrt(x0 ** 2 + y0 ** 2)
    h0 = z0

    if x0 ** 2 + y0 ** 2 != z0 ** 2 / a ** 2:
        raise ValueError("The start point is not on the cone.")

    polarAngleCone = np.linspace(0, 2 * np.pi, 100)
    radiusCone = np.linspace(0, np.sqrt(x0 ** 2 + y0 ** 2), 100)
    ThetaCone, RCone = np.meshgrid(polarAngleCone, radiusCone)
    XCone = RCone * np.cos(ThetaCone)
    YCone = RCone * np.sin(ThetaCone)
    ZCone = np.sqrt(a ** 2 * (XCone ** 2 + YCone ** 2))

    theta0 = np.arctan2(y0, x0)
    t_max = h0 / (V * np.sin(phi))
    t = np.linspace(0, t_max, 30)
    z = h0 - V * np.sin(phi) * t
    r = z / np.tan(phi)
    theta = theta0 + V * np.cos(phi) * t / r0
    x = r * np.cos(theta)
    y = r * np.sin(theta)

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.plot_surface(XCone, YCone, ZCone, color='gray', alpha=0.5)
    ax.plot(x, y, z, color='c')
    ax.scatter([x0], [y0], [z0], color='red')
    ax.scatter([0], [0], [0], color='red')
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')

    plt.show()
    return True
