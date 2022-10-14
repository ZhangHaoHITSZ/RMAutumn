#include "kalman.h"
#define gravity 9.8
#define ARR_NUM 20
//卡尔曼滤波就是在已知运动方程和观测方程时 得到系统最优状态估计的一种滤波器
//需要知道 初始状态的均值和协方差 噪声的协方差  ABH矩阵 输入的形式 和观测值
int main(int argc, char *argv[]) {
    Eigen::VectorXd x;
    Eigen::MatrixXd P0;
    Eigen::MatrixXd Q;
    Eigen::MatrixXd R;
    Eigen::MatrixXd A;
    Eigen::MatrixXd B;
    Eigen::MatrixXd H;
    Eigen::VectorXd z0;
    Eigen::VectorXd u_v;
    x.resize(2);
    // 初始状态其实是多维高斯分布的随机变量 用期望和协方差来描述即可 期望指的是随机变量最可能的取值
    // 协方差指的是这个取值的置信程度 状态的期望
    x(0) = 1900;
    x(1) = 10;
    // 状态的协方差
    P0.resize(2, 2);
    P0.setZero();
    P0(0, 0) = 100;
    P0(1, 1) = 2;
    // 观测方程上 噪声的协方差矩阵
    Q.resize(1, 1);
    Q.setIdentity();
    // 运动方程上 噪声的协方差矩阵
    R.resize(2, 2);
    R.setIdentity();
    // 运动方程 系统矩阵
    A.resize(2, 2);
    A.setIdentity();
    // 和输入相关的矩阵
    B.resize(2, 2);
    B.setIdentity();
    // 观测矩阵
    H.resize(1, 2);
    H(0, 0) = 1;
    H(0, 1) = 0;
    // 观测值
    z0.resize(1);
    // z0(0)=1994.5;
    //输入向量 在这里为一定值
    u_v.resize(2, 1);
    u_v(0) = -0.5 * gravity;
    u_v(1) = gravity;

    double arr[ARR_NUM] = {1994.5, 1979.4, 1955.4, 1921.4, 1877.7, 1825.0, 1759.8, 1686.7, 1603.6, 1509.2,
                           1407.6, 1294.4, 1172.4, 1039.9, 898.0,  745.5,  585.0,  412.5,  231.8,  39.9};
    // 构造函数
    Kalman ka(2, 1, 2);
    // 定义该对象的成员变量
    ka.Init_Par(x, P0, R, Q, A, B, H, u_v);

    for (int i = 0; i < ARR_NUM; i++) {
        z0(0) = arr[i];
        std::cout << "the " << (i + 1) << " th time predict" << std::endl;
        //调用成员函数 对自身对象的成员函数进行操作
        // 算出先验的状态变量均值和协方差
        ka.Predict_State();
        ka.Predict_Cov();
        // 计算卡尔曼增益
        ka.Mea_Resd(z0);
        // ka.Cal_Gain();
        ka.Update_State();
        ka.Update_Cov();
        std::cout << ka.m_x << std::endl;
        std::cout << "*************" << std::endl;
    }

    // cout<<ka.m_x<<endl;
    // cout<<ka.m_A<<endl;
    // cout<<ka.m_B<<endl;
    // cout<<ka.m_H<<endl;
    return 0;
}