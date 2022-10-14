#include "kalman.h"
Kalman::Kalman() {}
Kalman::Kalman(int statesize, int measize, int usize) {
    m_StateSize = statesize;
    m_MeaSize = measize;
    m_USize = usize;

    m_x.resize(statesize);
    m_x.setZero();

    m_u.resize(usize);
    m_u.setZero();

    m_z.resize(measize);
    m_z.setZero();

    m_A.resize(statesize, statesize);
    m_A.setIdentity();

    m_B.resize(statesize, usize);
    m_B.setZero();

    m_P.resize(statesize, statesize);
    m_P.setIdentity();

    m_H.resize(measize, statesize);
    m_H.setZero();

    m_R.resize(statesize, statesize);
    m_R.setZero();

    m_Q.resize(measize, measize);
    m_Q.setZero();

    m_iden_mat.resize(statesize, statesize);
    m_iden_mat.setIdentity();
}
void Kalman::Init_Par(Eigen::VectorXd& x, Eigen::MatrixXd& P, Eigen::MatrixXd& R, Eigen::MatrixXd& Q,
                      Eigen::MatrixXd& A, Eigen::MatrixXd& B, Eigen::MatrixXd& H, Eigen::VectorXd& u) {
    m_x = x;
    m_P = P;
    m_R = R;
    m_Q = Q;
    m_A = A;
    m_B = B;
    m_H = H;
    m_u = u;
}

void Kalman::Predict_State() {
    Eigen::VectorXd tmp_state = m_A * m_x + m_B * m_u;
    m_x = tmp_state;
}

void Kalman::Predict_Cov() {
    Eigen::MatrixXd tmp_cov = m_A * m_P * m_A.transpose() + m_R;
    m_P = tmp_cov;
}

Eigen::VectorXd Kalman::Mea_Resd(Eigen::VectorXd& z) {
    m_z = z;
    Eigen::VectorXd tmp_res = m_z - m_H * m_x;
    return tmp_res;
}

Eigen::MatrixXd Kalman::Cal_Gain() {
    Eigen::MatrixXd tmp_gain = m_P * m_H.transpose() * (m_H * m_P * m_H.transpose() + m_Q).inverse();
    return tmp_gain;
}

void Kalman::Update_State() {
    Eigen::MatrixXd kal_gain = Cal_Gain();
    Eigen::VectorXd mea_res = Mea_Resd(m_z);
    m_x = m_x + kal_gain * mea_res;
}

void Kalman::Update_Cov() {
    Eigen::MatrixXd kal_gain = Cal_Gain();
    Eigen::MatrixXd tmp_mat = kal_gain * m_H;
    m_P = (m_iden_mat - tmp_mat) * m_P;
}
