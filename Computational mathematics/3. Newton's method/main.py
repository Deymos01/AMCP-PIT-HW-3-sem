from newton import *


def main():
    m = NewtonMethod()

    # task 1
    print("\n===== Newton method =====\n")
    m.classicMethod()

    # task 2
    print("\n===== Modified Newton method =====\n")
    m.modifiedMethod()

    # task 3
    print("\n===== Modified Newton method with only k iterations =====\n")
    m.modifiedMethodWithOnlyKIterations(5)

    # task 4
    print("\n===== Modified Newton method Jacobi every m iterations =====\n")
    m.modifiedMethodWithMIterations(10)

    # task 5
    print("\n===== Modified Newton method united =====\n")
    m.modifiedMethodTransition(7, 7)

    # task 6
    print("\n===== Modified Newton method (k < 7) =====\n")
    m.modifiedMethodWithOnlyKIterations(2)
    print("\n===== Modified Newton method (k = 7) =====\n")
    m.modifiedMethodWithOnlyKIterations(6)
    print("\n===== Modified Newton method (k > 7) =====\n")
    m.modifiedMethodWithOnlyKIterations(10)



if __name__ == '__main__':
    main()
