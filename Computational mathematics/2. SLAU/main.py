from matrix import *

def main():
    m = Matrix(5, 5)
    m.initRandomA()
    m.A[:,1] = m.A[:,0]
    m.A[:,2] = -m.A[:,0]
    print("\n===== A-matrix =====\n", m.A)
    m.luDecomposition()
    print("\n====== L-matrix =====\n", m.L)
    print("\n====== U-matrix =====\n", m.U)
    print("\n====== L*U-matrix =====\n", m.L @ m.U)
    print("\n====== P*A*Q-matrix =====\n", m.P @ m.A @ m.Q)
    print("\n====== Determinant =====\n", m.determinant())
    b = np.array([1, 2, 3, 4, 5])
    bPerm = m.P @ b
    x = m.solveLU(bPerm)
    print("\n====== SLAE solution =====\n", x)
    print("\n====== Check SLAE solution =====\n", m.A @ x - b)

    invMatrix = m.inverse()
    print("\n===== Inverse matrix =====\n", invMatrix)
    print("\n===== Check inverse matrix =====\n", m.A @ invMatrix)
    print("\n===== Condition number =====\n", m.conditionNumber())

    m.qrDecomposition()
    print("\n====== Q-matrix =====\n", m.Q)
    print("\n====== R-matrix =====\n", m.R)
    print("\n====== Q*R-matrix =====\n", m.Q @ m.R)
    x = m.solveQR(b)
    print("\n====== QR solution =====\n", x)
    print("\n====== Check QR solution =====\n", m.A @ x - b)

    m.initDiagonalDominantRandomA()
    print("\n====== Jacobi method =====\n", m.jacobi(b))
    print("\n====== Seidel method =====\n", m.seidel(b))

if __name__ == "__main__":
    main()