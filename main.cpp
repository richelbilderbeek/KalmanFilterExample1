///Kalman filter example
///Merged from www.adrianboeing.com and http://greg.czerniak.info/guides/kalman1

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>

#include <boost/random/normal_distribution.hpp>
#include <boost/random/lagged_fibonacci.hpp>
///Obtain a random number from a normal distribution
///From http://www.richelbilderbeek.nl/CppGetRandomNormal.htm
double GetRandomNormal(const double mean = 0.0, const double sigma = 1.0)
{
  boost::normal_distribution<double> norm_dist(mean, sigma);
  static boost::lagged_fibonacci19937 engine;
  const double value = norm_dist.operator () <boost::lagged_fibonacci19937>((engine));
  return value;
}

///Context:
///A constant DC voltage measured with a noisy multimeter
int main()
{
  //initial values for the kalman filter
  double x_est_last = 0.0; //V
  double p_last = 0.0;
  //the noise in the system
  const double process_noise = 0.0001; //Q: Process noise: How to estimate this?
  const double measurement_noise_estimate = 0.1; //R: Measurement noise: How to estimate this?
  const double x_real = 1.25; //The real voltage, the one we wish to measure
  const double x_real_noise = 0.25; //Standard deviation of the noise in measuring the x_real

  //initialize with a measurement
  x_est_last = 10.0; //Just guess that the first measurement will be about 10V
  p_last = 1.0; //Just a guess

  std::cout << "Real,measured,Kalman\n";
  for (int i=0;i!=100;++i)
  {
    /// 1/7) State prediction
    const double x_current = x_est_last;
    /// 2/7) Covariance prediction
    const double p_current = p_last + process_noise;
    /// 3/7) Innovation (y with a squiggle above it)
    const double z_measured = x_real + GetRandomNormal(0.0,x_real_noise); //the noisy measurement
    const double innovation = z_measured - x_current;
    /// 4/7) Innovation covariance (S)
    const double innovation_covariance = p_current + measurement_noise_estimate;
    /// 5/7) Kalman gain (K)
    const double kalman_gain = p_current / innovation_covariance;
    /// 6/7) Update state prediction
    x_est_last = x_current + (kalman_gain * innovation);
    /// 7/7) Update covariance prediction
    p_last = (1.0 - kalman_gain) * p_current;

    //We have our new system
    //Real,measured,Kalman\n";
    std::cout << x_real << "," << z_measured << "," << x_est_last << '\n';
  }
}
