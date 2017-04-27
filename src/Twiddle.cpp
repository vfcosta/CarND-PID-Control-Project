#include "Twiddle.h"
#include <limits>
#include <iostream>

using namespace std;

Twiddle::Twiddle() {
  best_err = numeric_limits<double>::max();
  count = 0;
}

Twiddle::~Twiddle() {}

void Twiddle::Init(double Kp, double Ki, double Kd) {
  p[0] = Kp;
  p[1] = Kd;
  p[2] = Ki;
  count = 1; // skip initial update of coefficients
}

double *Twiddle::Coefficients() {
  return p;
}

void Twiddle::Update(double cte) {
//  if (SumPercent()<=tolerance) return;

  if (count == 0) {
    cout << "Twiddle iteration start" << endl;
    error = 0;
    UpdateCoefficients();
  }
  if (count >= limit) {
    cout << "Twiddle iteration end" << endl;
    count = 0;
    Evaluate(error);
    if (percent!=0.9) index = (index+1)%3;
    return;
  }
  error += cte * cte;
  DebugOutput();
  count++;
}

void Twiddle::Evaluate(double err) {
  if (err < best_err) {
    cout << "Twiddle found new best" << endl;
    best_err = err;
    percent = 1.1;
    modifier = 1;
    best_p[0] = p[0];
    best_p[1] = p[1];
    best_p[2] = p[2];
    UpdatePercent();
  } else {
    modifier = -2;
    if (percent==0.9) {
      UpdatePercent();
      percent = 1.1;
    } else {
      percent = 0.9;
    }
  }
}

void Twiddle::UpdateCoefficients() {
  double coef = p[index] + modifier * dp[index];
  if (coef > 0) p[index] = coef;
}

void Twiddle::UpdatePercent() {
  cout << "UPDATE PERCENT " << percent << endl;
  dp[index] *= percent;
}

double Twiddle::SumPercent() {
  double sum = 0;
  for(int i=0; i<3; i++) {
    sum += dp[i];
  }
  return sum;
}

void Twiddle::DebugOutput() {
  cout << "[" << count << "] Twiddle Update: p=";
  for(int i=0; i<3; i++) {
    cout << p[i] << " ";
  }
  cout << " dp=";
  for(int i=0; i<3; i++) {
    cout << dp[i] << " ";
  }
  cout << " best_p=";
  for(int i=0; i<3; i++) {
    cout << best_p[i] << " ";
  }
  cout << " error: " << error << " best_err: " << best_err << " modifier: " << modifier << " percent: " << percent << endl;
}
