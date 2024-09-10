import numpy as np
import matplotlib.pyplot as plt
# 模型描述：小车位置模型

# 预测过程
dt = 0.005
position_last, position_hat = 0, 0
v_last = 0
a = 3  # 加速度，即为系统的输入
position_matrix = np.array([position_last, v_last]) # 状态矩阵
A = np.array([[1, dt],
              [0, 1]]) # 特征矩阵
B = np.array([0.5 * dt * dt, dt]) # 输入矩阵
Q = np.array([[0.25, 0],
              [0, 0.72]]) # 误差协方差噪声矩阵
P = np.array([[0, 0],
              [0, 0]]) # 误差协方差矩阵
H = np.array([1, 0]) # 测量矩阵(测量方程: Z(k) = HX(k) + V(k)  )
R = 0.135 # 位置测量噪声(在陀螺仪中则为角度测量噪声(零漂))
t = np.linspace(0, 2 * np.pi, 1000)
Z = np.sin(t)

positions_hat = []
v_hat = []

for i in range(1, 1000):
    # 先验估计
    position_hat_prior = A @ position_matrix + B * a
    P = A @ P @ A.T + Q
    # 计算卡尔曼增益
    K = (P @ H.T)/(H @ P @ H.T + R)

    # 校正
    if i < len(Z):  # 确保不会越界
        position_hat = position_hat_prior + K * (Z[i] - H @ position_hat_prior)
        P = (np.eye(2) - K @ H) @ P
        
        #更新状态
        position_matrix = position_hat
        positions_hat.append(position_hat[0])
        v_hat.append(position_hat[1])

# 使用 matplotlib 绘制数据
plt.figure(figsize=(10, 5))
plt.plot(t[:len(positions_hat)], Z[:len(positions_hat)], label='True Position', color='blue')
plt.plot(t[:len(positions_hat)], positions_hat, label='Estimated Position', color='red', linestyle='--')
plt.plot(t[:len(v_hat)], v_hat, label='speed', color='black')
plt.title('Realty and Estimate')
plt.xlabel('Time')
plt.ylabel('Position or Speed')
plt.legend()
plt.grid(True)
plt.show()
