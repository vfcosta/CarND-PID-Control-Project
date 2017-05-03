#include "PID.h"

using namespace std;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;
  this->p_error = 0;
  this->d_error = 0;
  this->i_error = 0;
}

void PID::UpdateError(double cte) {
  this->d_error = cte - this->p_error;
  this->p_error = cte;
  this->i_error += cte;
}

double PID::TotalError() {
  return this->i_error;
}

double PID::Calculate(double cte) {
  this->UpdateError(cte);
  return -this->Kp * this->p_error - this->Kd * this->d_error - this->Ki * this->i_error;
}

void PID::UpdateCoefficients(double coef[]) {
  this->Kp = coef[0];
  this->Kd = coef[1];
  this->Ki = coef[2];
}