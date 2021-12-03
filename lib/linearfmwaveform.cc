#include "linearfmwaveform.h"

std::vector<std::complex<double>> LinearFMWaveform::pulse() {
  // Sample interval
  double ts = 1 / sampRate();
  // Number of samples per pulse
  int nSampsPulse = static_cast<int>(sampRate() * pulsewidth());
  double t;
  std::vector<std::complex<double>> wave(nSampsPulse, 0);
  for (int n = 0; n < nSampsPulse; n++) {
    t = n * ts;
    double phase = -bandwidth() / 2 * t +
                   bandwidth() / (2 * pulsewidth()) * std::pow(t, 2);
    wave[n] = std::exp(Im * (double)(2 * M_PI) * phase);
  }
  return wave;
}

LinearFMWaveform::LinearFMWaveform() : PulsedWaveform() { d_bandwidth = 0; }

LinearFMWaveform::LinearFMWaveform(double bandwidth, double pulsewidth,
                                   double prf, double sampRate)
    : PulsedWaveform(pulsewidth, prf, sampRate) {
  d_bandwidth = bandwidth;
}

LinearFMWaveform::LinearFMWaveform(double bandwidth, double pulsewidth,
                                   std::vector<double> prf, double sampRate)
    : PulsedWaveform(pulsewidth, prf, sampRate) {
  d_bandwidth = bandwidth;
}

LinearFMWaveform::~LinearFMWaveform() {}