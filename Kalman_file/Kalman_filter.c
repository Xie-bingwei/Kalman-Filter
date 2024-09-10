#include "Kalman.h"
// 陀螺仪滤波模型

float K1 = 0.02;
float angle, angle_dot;
float Q_angle = 0.001; // 过程噪声的协方差
float Q_gyro = 0.003; //0.03 过程噪声的协方差 过程噪声的协方差为一个一行两列矩阵
float R_angle = 0.5; // 测量噪声的协方差 既测量偏差
float dt = 0.005; //
char C_0 = 1;
float Q_bias, Angle_err;
float PCt_0, PCt_1, E;
float K_0, K_1, t_0, t_1;
float Pdot[4] =
        { 0, 0, 0, 0 };
float PP[2][2] =
                {
                { 1, 0 },
                { 0, 1 }
                };

// 协方差矩阵，卡尔曼增益更新
float kalman_filter(kal_filter* k_flt, float input)
{
    
    k_flt->input = input;
    k_flt->K = (k_flt->C_last) / (k_flt->C_last + k_flt->R);
    k_flt->X = k_flt->X_last + k_flt->K * (k_flt->input - k_flt->X_last);
    k_flt->C = (1 - k_flt->K) * (k_flt->C_last);

    /*时间更新，2组方程*/
    k_flt->X_last = k_flt->X;
    k_flt->C_last = k_flt->C + k_flt->Q;

    return k_flt->X;
}

void Kalman_Filter(float Accel, float Gyro)
{
    angle += (Gyro - Q_bias) * dt;		   //先验估计
    Pdot[0] = Q_angle - PP[0][1] - PP[1][0]; // Pk-先验估计误差协方差的微分

    Pdot[1] = -PP[1][1];
    Pdot[2] = -PP[1][1];
    Pdot[3] = Q_gyro;
    PP[0][0] += Pdot[0] * dt;   		   // Pk-先验估计误差协方差微分的积分
    PP[0][1] += Pdot[1] * dt;   		   // =先验估计误差协方差
    PP[1][0] += Pdot[2] * dt;
    PP[1][1] += Pdot[3] * dt;

    Angle_err = Accel - angle;			   //zk-先验估计

    PCt_0 = C_0 * PP[0][0];
    PCt_1 = C_0 * PP[1][0];

    E = R_angle + C_0 * PCt_0;

    K_0 = PCt_0 / E;
    K_1 = PCt_1 / E;

    t_0 = PCt_0;
    t_1 = C_0 * PP[0][1];

    PP[0][0] -= K_0 * t_0;		 		    //后验估计误差协方差
    PP[0][1] -= K_0 * t_1;
    PP[1][0] -= K_1 * t_0;
    PP[1][1] -= K_1 * t_1;

    angle += K_0 * Angle_err;	 			//后验估计
    Q_bias += K_1 * Angle_err;	 			//后验估计
    angle_dot = Gyro - Q_bias;		 	//输出值(后验估计)的微分=角速度
}

void First_order_filter(float angle_m, float gyro_m)
{
    angle = K1 * angle_m + (1 - K1) * (angle + gyro_m * 0.005);
}

