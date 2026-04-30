import matplotlib.pyplot as plt
import matplotlib.patches as patches

fig, ax = plt.subplots(figsize=(10, 5))
ax.set_xlim(0, 10)
ax.set_ylim(0, 6)
ax.set_aspect('equal')
ax.axis('off')

# --- Источник ЭДС ---
# Батарея: длинная и короткая черта
ax.plot([1.0, 1.0], [2.0, 3.0], 'k', linewidth=4)   # длинная (+)
ax.plot([1.3, 1.3], [2.2, 2.8], 'k', linewidth=4)   # короткая (–)
ax.text(0.75, 3.2, '+', fontsize=14, ha='center')
ax.text(0.75, 1.8, '–', fontsize=14, ha='center')
ax.text(0.2, 2.5, 'ε, r', fontsize=14, ha='center', va='center')

# --- Верхний провод ---
ax.plot([1.0, 8.0], [3.0, 3.0], 'k', linewidth=2)

# --- Амперметр ---
circle_A = patches.Circle((2.5, 3.0), 0.4, edgecolor='black', facecolor='white', linewidth=2)
ax.add_patch(circle_A)
ax.text(2.5, 3.0, 'A', fontsize=16, ha='center', va='center', fontweight='bold')

# --- Продолжение верхнего провода ---
ax.plot([2.9, 7.5], [3.0, 3.0], 'k', linewidth=2)
# Спуск к резистору
ax.plot([7.5, 7.5], [3.0, 2.2], 'k', linewidth=2)

# --- Магазин сопротивлений R ---
rect_R = patches.Rectangle((7.0, 1.2), 1.0, 2.0, edgecolor='black', facecolor='white', linewidth=2)
ax.add_patch(rect_R)
ax.text(7.5, 2.2, 'R', fontsize=16, ha='center', va='center')
ax.text(7.5, 0.9, '(0–1000 Ом)', fontsize=9, ha='center')

# --- Нижний провод ---
ax.plot([7.5, 1.0], [1.2, 1.2], 'k', linewidth=2)
ax.plot([1.0, 1.0], [1.2, 2.0], 'k', linewidth=2)   # заход в источник

# --- Вольтметр (параллельно R) ---
# Отводы вверх и вниз от концов R
ax.plot([7.0, 6.5], [2.2, 2.2], 'k', linewidth=1.5)   # верхний отвод
ax.plot([6.5, 6.5], [2.2, 4.0], 'k', linewidth=1.5)
ax.plot([7.0, 6.5], [1.2, 1.2], 'k', linewidth=1.5)   # нижний отвод
ax.plot([6.5, 6.5], [1.2, 0.5], 'k', linewidth=1.5)
# Сам вольтметр
circle_V = patches.Circle((6.5, 2.25), 0.4, edgecolor='black', facecolor='white', linewidth=2)
ax.add_patch(circle_V)
ax.text(6.5, 2.25, 'V', fontsize=16, ha='center', va='center', fontweight='bold')
# Соединение вольтметра с вертикальными проводами
ax.plot([6.1, 6.1], [4.0, 2.65], 'k', linewidth=1.5)
ax.plot([6.1, 6.1], [1.85, 0.5], 'k', linewidth=1.5)

# --- Подписи ---
ax.text(4.5, 3.3, 'I', fontsize=14, color='red')
ax.text(2.5, 2.3, 'I', fontsize=14, color='red')
ax.text(7.5, 3.3, 'I', fontsize=14, color='red')
ax.text(4.5, 0.9, 'I', fontsize=14, color='red')

ax.set_title('Рис. 13.1. Принципиальная схема установки', fontsize=14, fontweight='bold', pad=15)
plt.tight_layout()
plt.show()