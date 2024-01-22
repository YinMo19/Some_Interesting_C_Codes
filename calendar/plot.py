import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

# Define the function for the curve fitting
def func(x, a, b, c):
    """
    Calculate the value of a * exp(-b * x) + c.

    Args:
        x (numeric): The input value.
        a (numeric): Coefficient for the exponential term.
        b (numeric): Exponential decay rate.
        c (numeric): Constant term.

    Returns:
        numeric: The result of the function evaluation.
    """
    return a * np.exp(-b * x) + c

# Generate some sample data
x_data = np.linspace(0, 4, 50)
y = func(x_data, 2.5, 1.3, 0.5)
np.random.seed(1729)
y_noise = 0.2 * np.random.normal(size=x_data.size)
y_data = y + y_noise

# Perform the curve fitting
popt, pcov = curve_fit(func, x_data, y_data)

# Plot the data and the fitted curve
plt.figure()
plt.scatter(x_data, y_data, label='Data')
plt.plot(x_data, func(x_data, *popt), 'r-', label='Fitted curve')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Curve Fitting with Fitted Equation')
plt.text(2, 3, r'$f(x) = %0.2f \exp(-%0.2f x) + %0.2f$' % (popt[0], popt[1], popt[2]), fontsize=12)
plt.legend()
plt.show()