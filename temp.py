import numpy as np
import matplotlib.pyplot as plt

# Экспериментальные точки (J, r) — именно в таком порядке (J, r)
exp_J = np.array([1.62e-2, 2.16e-2, 1.088e-2])
exp_r = np.array([11.5e-2, 21.5e-2, 1.0e-2])

# Теоретические точки (J, r)
theor_J = np.array([1.333e-2, 2.165e-2, 1.003e-2])
theor_r = np.array([11.5e-2, 21.5e-2, 1.0e-2])

# Функция линейной регрессии y = a*x + b
def linreg(x, y):
    n = len(x)
    sum_x = np.sum(x)
    sum_y = np.sum(y)
    sum_xy = np.sum(x * y)
    sum_x2 = np.sum(x ** 2)
    
    a = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x ** 2)
    b = (sum_y - a * sum_x) / n
    return a, b

# Коэффициенты для экспериментальной прямой (J = a_exp * r + b_exp)
a_exp, b_exp = linreg(exp_r, exp_J)
# Коэффициенты для теоретической прямой
a_theor, b_theor = linreg(theor_r, theor_J)

print("=== Экспериментальная прямая ===")
print(f"J = {a_exp:.6f} * r + {b_exp:.6f}")
print()
print("=== Теоретическая прямая ===")
print(f"J = {a_theor:.6f} * r + {b_theor:.6f}")

# Диапазон r для построения прямых
r_min = 0
r_max = max(max(exp_r), max(theor_r)) * 1.1
r_fit = np.linspace(r_min, r_max, 100)

# Значения J для прямых
J_exp_fit = a_exp * r_fit + b_exp
J_theor_fit = a_theor * r_fit + b_theor

# Построение графика
plt.figure(figsize=(8, 6))

# Экспериментальные точки и прямая
plt.scatter(exp_r, exp_J, color='red', s=80, marker='o', label='Эксперимент (точки)')
plt.plot(r_fit, J_exp_fit, 'r--', linewidth=2, label=f'Эксперимент: J = {a_exp:.4f}·r + {b_exp:.4f}')

# Теоретические точки и прямая
plt.scatter(theor_r, theor_J, color='blue', s=80, marker='s', label='Теория (точки)')
plt.plot(r_fit, J_theor_fit, 'b--', linewidth=2, label=f'Теория: J = {a_theor:.4f}·r + {b_theor:.4f}')

# Оформление
plt.xlabel('r (м)', fontsize=12)
plt.ylabel('J (кг·м²)', fontsize=12)
plt.title('Зависимость момента инерции от расстояния грузов до оси вращения', fontsize=14)
plt.legend(fontsize=10)
plt.grid(True, alpha=0.3)
plt.axhline(0, color='black', linewidth=0.5)
plt.axvline(0, color='black', linewidth=0.5)

# Научный формат осей
plt.ticklabel_format(style='sci', axis='both', scilimits=(-2, -2))

plt.tight_layout()
plt.show()