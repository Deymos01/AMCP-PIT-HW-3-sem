from berni import berni

def test_berni_1() -> None:
    f = berni(3, 0)
    assert(f(0) == 1)
    assert(abs(f(0.5) - 0.125) < 1e-8)
    assert(abs(f(0.75) - 1.5625e-2) < 1e-8)
    assert(f(1) == 0)


def test_berni_2() -> None:
    f = berni(3, 3)
    assert(f(0) == 0)
    assert(abs(f(0.5) - 0.125) < 1e-8)
    assert(abs(f(0.25) - 1.5625e-2) < 1e-8)
    assert(f(1) == 1)


def test_berni_3() -> None:
    f = berni(4, 1)
    assert(f(0) == 0)
    assert(abs(f(0.5) - 0.25) < 1e-8)
    assert(abs(f(0.25) - 4.21875e-1) < 1e-8)
    assert(f(1) == 0)
