import kotlin.math.*

// TASK №14

// arctg(sqrt(0.9x + 1)/(1 - x^2)) + sin(3x + 0.6); x = 0.2(0.01)03.

fun sqrtHeron(value: Double, error: Double): Double {
    var x: Double = value / 2
    var currX: Double = 0.5 * (x + value / x)
    while (abs(currX - x) > error) {
        x = currX
        currX = 0.5 * (x + value / x)
    }
    return currX
}

fun atanTaylor(value: Double, error: Double): Double {
    val funValue: Double = if (abs(value) > 1) 1 / value else value
    var result: Double = funValue
    var currElem: Double = funValue
    var n: Int = 1

    while (abs(currElem) > error) {
        currElem *= (-1) * (funValue * funValue) * (2 * n - 1) / (2 * n + 1)
        result += currElem
        ++n
    }

    if (abs(value) > 1) {
        result = PI / 2 - result
    }

    return result
}

fun sinTaylor(value: Double, error: Double): Double {
    var result: Double = value
    var currElem: Double = value
    var n: Int = 1
    while (abs(currElem) > error) {
        currElem *= (-1) * (value * value) / ((2 * n + 1) * (2 * n))
        result += currElem
        ++n
    }
    return result
}

fun solve1(start: Double, end: Double, step: Double): Unit {
    var x: Double = start
    while (x <= end) {

        val accurateSolution: Double = atan(sqrt(0.9 * x + 1) / (1 - x * x)) + sin(3 * x + 0.6)

        val resSqrt: Double = sqrtHeron((0.9 * x + 1), 1e-6 / 1.32)
        val resATan: Double = atanTaylor(resSqrt / (1 - x * x), 1e-6 / 3)
        val resSin: Double = sinTaylor(3 * x + 0.6, 1e-6 / 3)

        val approxSolution: Double = resATan + resSin

        println("  ${"%.2f".format(x)}  |  \t${"%.8f".format(accurateSolution)}\t    |  \t${"%.8f".format(approxSolution)}\t    |  ${"%.8f".format(accurateSolution - approxSolution)}")

        x += step
    }
}

fun solve2(start: Double, end: Double, step: Double): Unit {
    var x: Double = start
    while (x <= end) {

        val accurateSolution: Double = atan(sqrt(1 - 0.6 * x)) / sin(1 + 0.4 * x)

        val resSqrt: Double = sqrtHeron(1 - 0.6 * x, 1e-6 / 1.65)
        val resATan: Double = atanTaylor(resSqrt, 1e-6 / 3.42)
        val resSin: Double = sinTaylor(1 + 0.4 * x, 1e-6 / 3.24)

        val approxSolution: Double = resATan / resSin

        println("  ${"%.2f".format(x)}  |  \t${"%.8f".format(accurateSolution)}\t    |  \t${"%.8f".format(approxSolution)}\t    |  ${"%.8f".format(accurateSolution - approxSolution)}")

        x += step
    }
}

fun main() {
    val start: Double = 0.2
    val end: Double = 0.31
    val step: Double = 0.01

    println("\tx\t|\t\tz(x)\t\t|\t\tz'(x)\t\t|\terror\t")
    println("--------|-------------------|-------------------|------------------")
    solve1(start, end, step)
}