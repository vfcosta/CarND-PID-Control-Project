#ifndef TWIDDLE_H
#define TWIDDLE_H

class Twiddle {
public:
  
  Twiddle();

  virtual ~Twiddle();

  void Init(double Kp, double Ki, double Kd);

  void Update(double cte);

  void Evaluate(double err);

  void UpdatePercent();

  void UpdateCoefficients();

  double *Coefficients();

  double SumPercent();

private:
  double best_err;
  double error = 0;
  double tolerance = 0.2;
  long count;
  long limit = 1000;
  double dp[3] = {0.01, 0.02, 0.001};
  double p[3] = {0.0, 0.0, 0.0};
  double best_p[3] = {0.0, 0.0, 0.0};

  int modifier = 1;
  double percent = 1.1;

  int index = -1;

  void DebugOutput();
};

#endif /* TWIDDLE_H */
