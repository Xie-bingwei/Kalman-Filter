# Kalman-Filter

卡尔曼滤波器实际上是误差的数据融合。其后验估计公式可看为   Y(s) = K * X(s) + (1 - K)Z(s), 其本质就是数据融合得到一个误差更小的数据

这里给出实际机器人，智能车，飞控开发中的姿态滤波模型(C/C++)和运动估计模型(Python)的仿真



估计



1.先验估计: X(k|k-1) = A(k,k-1)*X(k-1|k-1) + B(k)*u(k)

2.先验协方差更新: P(k|k-1) = A(k,k-1)*P(k-1|k-1)*A(k,k-1)'+Q(k)



校正



1.计算卡尔曼增益 : K(k) = P(k|k-1)*H(k)' / (H(k)*P(k|k-1)*H(k)' + R(k)) 

2.测量更新: X(k|k) = X(k|k-1)+K(k)*(Z(k)-H(k)*X(k|k-1))

3.更新后验协方差: P(k|k) = (I-K(k)*H(k))*P(k|k-1)



在陀螺仪模型中，校正过程的几个数组相乘实质为矩阵相乘化简后变为方程组的形势，在运动模型仿真中，通过Python的矩阵运算省略了这一步


