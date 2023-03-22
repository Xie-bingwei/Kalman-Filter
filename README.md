# Kalman-Filter

这里仅提供一种思路

Just a way of thinking

先验估计
1.时间更新: X(k|k-1) = A(k,k-1)*X(k-1|k-1) + B(k)*u(k)

2.先验协方差更新: P(k|k-1) = A(k,k-1)*P(k-1|k-1)*A(k,k-1)'+Q(k)

后验估计
1.计算卡尔曼增益 : K(k) = P(k|k-1)*H(k)' / (H(k)*P(k|k-1)*H(k)' + R(k)) 

2.测量更新: X(k|k) = X(k|k-1)+K(k)*(Z(k)-H(k)*X(k|k-1))

3.更新后验协方差: P(k|k) =£¨I-K(k)*H(k)£©*P(k|k-1)
