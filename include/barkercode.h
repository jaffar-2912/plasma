#ifndef D44B01D2_E99D_42FF_9E9A_BFDE907AE626
#define D44B01D2_E99D_42FF_9E9A_BFDE907AE626
#include "phasecode.h"
#include "phasecodedwaveform.h"
#include "pulsedwaveform.h"

class BarkerCode : public PulsedWaveform, public PhaseCodedWaveform {
 public:
  /**
   * @brief Generate data for a single pulse
   *
   * @return std::vector<std::complex<double>> Pulse data
   */
  std::vector<std::complex<double>> pulse();
  /**
   * @brief Generate data for a full PRF schedule
   *
   * @return std::vector<std::complex<double>> Pulse data for at least 1 PRF
   */
  std::vector<std::complex<double>> pulseTrain();

  /**
   * @brief Construct a new Barker Code object
   *
   */
  BarkerCode();

  /**
   * @brief Construct a new Barker Code object
   *
   * @param n Code length
   */
  BarkerCode(int n);

  BarkerCode(int n, double chipwidth, double prf, double sampRate);

  BarkerCode(int n, double chipwidth, std::vector<double> prf, double sampRate);
};

#endif /* D44B01D2_E99D_42FF_9E9A_BFDE907AE626 */
