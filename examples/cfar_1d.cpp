/**
 * Created on Tue Jan 04 2022
 *
 * Shane Flandermeyer, shaneflandermeyer@gmail.com
 *
 * A simple example usage of the CFAR detection object when the input is
 * gaussian noise with a time-varying variance. This example is adapted from
 * https://www.mathworks.com/help/phased/ug/constant-false-alarm-rate-cfar-detection.html
 */

#include "cfar.h"
#include "matrix-utils.h"

#include <random>
#include <Eigen/Dense>
#include <matplot/matplot.h>

using namespace plasma;
using namespace matplot;
using namespace Eigen;
int main() {

  //! CFAR parameters
  auto method = "CA";
  size_t num_guard_cells = 2;
  size_t num_train_cells = 200;
  auto pfa = 1e-3;
  CFARDetector ca_cfar {num_train_cells, num_guard_cells, pfa};

  //! Generate data
  // The input data is a square-law input signal with increasing noise power
  auto noise_power = pow(10, -10 / 10);
  size_t num_points = 10e3;
  // std::default_random_engine gen;
  MatrixX<std::complex<double>> rsamp(num_points, 1);
  MatrixXd x(rsamp.rows(), rsamp.cols());
  // Start with samples from a complex standard normal distribution
  std::mt19937 gen{1000};
  std::normal_distribution<> normal{0, 1};
  for (size_t i = 0; i < num_points; ++i)
    rsamp(i) = std::complex<double>(normal(gen), normal(gen));
  // Create the square-law input signal
  ArrayXd ramp = ArrayXd::LinSpaced(num_points, 1, 10);
  x = abs2(sqrt(noise_power * ramp / 2) * rsamp.array()).matrix();
  // x = hcat(x,x);

  //! Write to a file
  // std::vector<double> filevec(x.data(), x.data() + x.size());
  // write_binary<double>("/home/shane/bin.dat",filevec);

  //! Do CFAR
  DetectionReport detections = ca_cfar.detect(x);

  //! Figures
  // Input data
  std::vector<double> xvec(x.data(), x.data() + x.size());
  // Threshold
  std::vector<double> threshvec(detections.threshold.data(),
                                detections.threshold.data() +
                                    detections.threshold.size());
  // Detections
  std::vector<size_t> indices(detections.indices.col(0).data(),
                              detections.indices.col(0).data() +
                                  detections.indices.col(0).size());
  std::vector<double> detvec(detections.indices.size());
  for (size_t i = 0; i < detections.indices.size(); ++i)
    detvec[i] = x(detections.indices(i));

  plot(xvec);
  hold(true);
  plot(threshvec);
  plot(indices, detvec, "o");
  hold(false);
  show();
  return 0;
}