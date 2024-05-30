from bridgy import bridgy


def y2(x):
    return (x - 1.8)**2 + 1.3  # Пример функции y2(x)

def y1(x):
    return -x + 2.2   # Пример функции y1(x)

x_bridge, y1_bridge, y2_bridge = bridgy(y1, y2)
print("Координаты точки на берегу, соединенной мостом:")
print("x:", x_bridge)
print("y1(x):", y1_bridge)
print("y2(x):", y2_bridge)