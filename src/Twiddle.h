#ifndef TWIDDLE_H
#define TWIDDLE_H

class Twiddle {
public:
  
  Twiddle();

  virtual ~Twiddle();

  void Init(double Kp, double Ki, double Kd);

  bool Update(double cte);

  void Evaluate(double err);

  double *Coefficients();

  double SumPercent();

  void FinishIteration();

private:
  int status = 0;
  long count;
  double best_err;
  double error = 0;
  double tolerance = 0.2;
  double dp[3] = {1, 1, 1};
  double p[3] = {0.0, 0.0, 0.0};
  double best_p[3] = {0.0, 0.0, 0.0};

  int index = 0;

  void DebugOutput();
};

#endif /* TWIDDLE_H */
