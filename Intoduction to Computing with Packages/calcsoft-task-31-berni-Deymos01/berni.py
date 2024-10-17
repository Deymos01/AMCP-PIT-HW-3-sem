from math import factorial


def berni(n, k):
    def bernpoly(x):
        return (factorial(n) / (factorial(k) * factorial(n - k))) * x ** k * (1 - x) ** (n - k)

    return bernpoly
