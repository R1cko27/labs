import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rcParams

# Настройка шрифтов для корректного отображения кириллицы
rcParams['font.family'] = 'DejaVu Sans'
rcParams['font.size'] = 12

# Экспериментальные данные
I_ma = np.array([10.7, 13.0, 14.7, 16.0, 17.8, 18.4, 19.8, 21.0, 22.8, 26.9])  # мА
U_exp = np.array([10.82, 9.28, 8.15, 7.29, 6.08, 5.65, 4.76, 3.95, 2.80, 0.06])   # В
I_a = I_ma / 1000.0  # перевод в амперы

# Количество точек
n = len(I_a)

# Метод наименьших квадратов (МНК): U = ε - r*I
sum_I = np.sum(I_a)
sum_U = np.sum(U_exp)
sum_I2 = np.sum(I_a**2)
sum_IU = np.sum(I_a * U_exp)

r_coef = (n * sum_IU - sum_I * sum_U) / (n * sum_I2 - sum_I**2)  # = -r
epsilon = (sum_U + abs(r_coef) * sum_I) / n
r_int = abs(r_coef)  # внутреннее сопротивление

# Рассчитанные величины
U_fit = epsilon - r_int * I_a
I_k = epsilon / r_int  # ток короткого замыкания
I_m = epsilon / (2 * r_int)  # ток максимума полезной мощности
P1_max = epsilon**2 / (4 * r_int)

# Расчёт мощностей и КПД
P_full = I_a * epsilon
P_useful = I_a * U_exp
P_loss = I_a**2 * r_int
eta = U_exp / epsilon

# Дополнительные точки для гладких теоретических кривых
I_smooth = np.linspace(0, I_k, 200)
U_smooth = epsilon - r_int * I_smooth
P_full_smooth = epsilon * I_smooth
P_useful_smooth = epsilon * I_smooth - r_int * I_smooth**2
P_loss_smooth = r_int * I_smooth**2
eta_smooth = U_smooth / epsilon

# Точки максимума
I_smooth_m = epsilon / (2 * r_int)
P1_smooth_max = epsilon**2 / (4 * r_int)

# Вывод параметров в консоль
print(f"ЭДС источника:  ε = {epsilon:.3f} В")
print(f"Внутреннее сопротивление: r = {r_int:.1f} Ом")
print(f"Ток короткого замыкания: Iк = {I_k*1000:.2f} мА")
print(f"Ток максимальной полезной мощности: Im = {I_m*1000:.2f} мА")
print(f"Максимальная полезная мощность: P1max = {P1_max:.4f} Вт")

# Создание фигуры с четырьмя подграфиками
fig, axs = plt.subplots(2, 2, figsize=(14, 12))

# --- График 1: U(I) ---
axs[0, 0].plot(I_smooth*1000, U_smooth, 'b-', linewidth=2, label='Теоретическая прямая')
axs[0, 0].errorbar(I_ma, U_exp, xerr=0.15, yerr=0.075, fmt='ro', 
                    markersize=8, capsize=3, label='Экспериментальные точки')
# Экстраполяционные пунктирные линии
axs[0, 0].axhline(y=epsilon, color='gray', linestyle='--', alpha=0.7)
axs[0, 0].axvline(x=I_k*1000, color='gray', linestyle='--', alpha=0.7)
axs[0, 0].annotate(f'ε = {epsilon:.2f} В', xy=(0, epsilon), xytext=(-2, epsilon+0.5),
                   fontsize=11, color='gray')
axs[0, 0].annotate(f'Iк = {I_k*1000:.1f} мА', xy=(I_k*1000, 0), xytext=(I_k*1000-5, 0.5),
                   fontsize=11, color='gray')
axs[0, 0].set_xlabel('Сила тока I, мА')
axs[0, 0].set_ylabel('Напряжение U, В')
axs[0, 0].set_title('Зависимость напряжения от силы тока')
axs[0, 0].legend()
axs[0, 0].grid(True, alpha=0.3)

# --- График 2: Полная, полезная мощность и мощность потерь ---
axs[0, 1].plot(I_smooth*1000, P_full_smooth, 'b-', linewidth=2, label='Полная мощность P')
axs[0, 1].plot(I_smooth*1000, P_useful_smooth, 'r-', linewidth=2, label='Полезная мощность P₁')
axs[0, 1].plot(I_smooth*1000, P_loss_smooth, 'g-', linewidth=2, label='Потери мощности P₂')
# Экспериментальные точки
axs[0, 1].scatter(I_ma, P_full, color='blue', marker='o', s=60, zorder=5)
axs[0, 1].scatter(I_ma, P_useful, color='red', marker='s', s=60, zorder=5)
axs[0, 1].scatter(I_ma, P_loss, color='green', marker='^', s=60, zorder=5)
# Маркер максимума полезной мощности
axs[0, 1].axvline(x=I_m*1000, color='red', linestyle='--', alpha=0.5)
axs[0, 1].scatter([I_m*1000], [P1_smooth_max], color='darkred', s=100, zorder=6)
axs[0, 1].annotate(f'P₁max = {P1_smooth_max:.3f} Вт\nI = {I_m*1000:.1f} мА',
                   xy=(I_m*1000, P1_smooth_max),
                   xytext=(I_m*1000+2, P1_smooth_max-0.1),
                   fontsize=10, color='darkred',
                   arrowprops=dict(arrowstyle='->', color='darkred'))
axs[0, 1].set_xlabel('Сила тока I, мА')
axs[0, 1].set_ylabel('Мощность P, Вт')
axs[0, 1].set_title('Зависимость мощностей от силы тока')
axs[0, 1].legend()
axs[0, 1].grid(True, alpha=0.3)

# --- График 3: P₁(I) отдельно ---
axs[1, 0].plot(I_smooth*1000, P_useful_smooth, 'r-', linewidth=2, label='Теоретическая кривая')
axs[1, 0].scatter(I_ma, P_useful, color='red', marker='s', s=80, zorder=5, label='Эксперимент')
axs[1, 0].axvline(x=I_m*1000, color='gray', linestyle='--', alpha=0.5)
axs[1, 0].axhline(y=P1_smooth_max, color='gray', linestyle='--', alpha=0.5)
axs[1, 0].scatter([I_m*1000], [P1_smooth_max], color='darkred', s=120, zorder=6)
axs[1, 0].annotate(f'Максимум: {P1_smooth_max:.3f} Вт',
                   xy=(I_m*1000, P1_smooth_max),
                   xytext=(I_m*1000+3, P1_smooth_max-0.04),
                   fontsize=11, color='darkred',
                   arrowprops=dict(arrowstyle='->', color='darkred'))
axs[1, 0].set_xlabel('Сила тока I, мА')
axs[1, 0].set_ylabel('Полезная мощность P₁, Вт')
axs[1, 0].set_title('Зависимость полезной мощности')
axs[1, 0].legend()
axs[1, 0].grid(True, alpha=0.3)

# --- График 4: КПД η(I) ---
axs[1, 1].plot(I_smooth*1000, eta_smooth, 'b-', linewidth=2, label='Теоретическая прямая')
axs[1, 1].scatter(I_ma, eta, color='blue', marker='o', s=80, zorder=5, label='Эксперимент')
axs[1, 1].axhline(y=0.5, color='red', linestyle='--', alpha=0.5, label='η = 50%')
axs[1, 1].axvline(x=I_m*1000, color='gray', linestyle='--', alpha=0.5)
# Точка при токе максимальной мощности
eta_at_max = 1 - I_m * r_int / epsilon  # ≈ 0.5
axs[1, 1].scatter([I_m*1000], [eta_at_max], color='darkred', s=100, zorder=6)
axs[1, 1].annotate(f'η ≈ {eta_at_max:.2f} при P₁max',
                   xy=(I_m*1000, eta_at_max),
                   xytext=(I_m*1000-20, eta_at_max-0.4),
                   fontsize=11, color='darkred',
                   arrowprops=dict(arrowstyle='->', color='darkred'))
axs[1, 1].set_xlabel('Сила тока I, мА')
axs[1, 1].set_ylabel('КПД η')
axs[1, 1].set_title('Зависимость КПД от силы тока')
axs[1, 1].legend()
axs[1, 1].grid(True, alpha=0.3)

# Общий заголовок
plt.tight_layout(rect=[0, 0, 1, 0.96])
plt.show()