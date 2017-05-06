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

void Twiddle::FinishIteration() {
    cout << "Twiddle iteration end" << endl;
    count = 0;
    status++;
    Evaluate(error);
    if (status==0) index = (index+1)%2;
}

bool Twiddle::Update(double cte) {
//  if (SumPercent()<=tolerance) return;

  if (count == 0) {
    cout << "Twiddle iteration start" << endl;
    error = 0;
    if(status==0) p[index] += dp[index];
  }
  error += cte * cte;
  DebugOutput();
  count++;
  return count < 1300 && error < best_err;
}

void Twiddle::Evaluate(double err) {
  if (err < best_err && status > 0) {
    cout << "Twiddle found new best" << endl;
    best_err = err;
    dp[index] *= 1.1;
    best_p[0] = p[0];
    best_p[1] = p[1];
    best_p[2] = p[2];
    status = 0;
  } else {
    if(status==1) {
      p[index] -= 2 * dp[index];
    } else if(status == 2) {
      p[index] += dp[index];
      dp[index] *= 0.9;
      status = 0;
    }
  }
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
  cout << " error: " << error << " best_err: " << best_err << " index: " << index << " status: " << status << endl;
}
