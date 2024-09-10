#ifndef KALMAN_FILTERING_KALMAN_H
#define KALMAN_FILTERING_KALMAN_H

typedef struct Kalman_filter
{
    float C_last; /*上次预测过程协方差矩阵 C(k|k-1)*/
    float X_last; /*系统状态预测矩阵，列矩阵*/

    float Q; /*过程噪声协方差*/
    float R; /*量测噪声协方差*/

    float K; /*卡尔曼增益，列矩阵*/
    float X; /*估计输出矩阵，列矩阵*/
    float C; /*估计协方差矩阵C(k|k)*/

    float input; /*量测值，即Z(k)*/
} kal_filter;

extern float angle, angle_dot;
void Kalman_Filter(float Accel, float Gyro);
void First_order_filter(float angle_m, float gyro_m);
float kalman_filter(kal_filter* k_flt, float input);

#endif //KALMAN_FILTERING_KALMAN_H

