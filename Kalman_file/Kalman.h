typedef struct Kalman_filter
{
    float Last_prediction_cov; /* (k|k-1)*/
    float System_state_prediction_matrix; /*列矩阵*/

    float Process_noise_cov;
    float Measure_noise_cov;

    float K;                                                  /*卡尔曼增益，列矩阵*/
    float Optimal_output; /*最优估计输出矩阵，列矩阵*/
    float Optimal_cov_matrix; /*最优估计协方差矩阵C(k|k)*/

    float input; /*量测值，即Z(k)*/
} kal_filter;

void Kalman_Filter(float Accel, float Gyro);
