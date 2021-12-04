#include "plasma-dsp/phasecodedwaveform.h"

#include <iostream>
std::vector<std::complex<double>> PhaseCodedWaveform::pulse() {
  // Oversampling factor
  int nSampsChip = std::round(d_chipwidth * sampRate());
  std::vector<std::complex<double>> pulse(nSampsChip * d_nChips);
  // Create the oversampled waveform vector
  for (int i = 0; i < d_code.size(); i++) {
    std::fill(pulse.begin() + i * nSampsChip,
              pulse.begin() + (i + 1) * nSampsChip, std::exp(Im * d_code[i]));
  }
  return pulse;
}

PhaseCodedWaveform::PhaseCodedWaveform() {
  d_nChips = 0;
  d_chipwidth = 0;
  d_code = std::vector<double>();
}

PhaseCodedWaveform::PhaseCodedWaveform(int nChips, double chipwidth,
                                       std::vector<double> code) {
  d_nChips = nChips;
  d_chipwidth = chipwidth;
  d_code = code;
}
