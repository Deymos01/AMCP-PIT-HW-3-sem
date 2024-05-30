from scipy.optimize import minimize_scalar

def bridgy(y1, y2):
    def bridgy_length(x):
        return y2(x) - y1(x)

    result = minimize_scalar(bridgy_length, bounds=(-100, 100))
    return result.x, y1(result.x), y2(result.x)
