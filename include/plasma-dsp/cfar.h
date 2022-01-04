#ifndef D4D7CDC7_8DAA_42DF_A71A_3840A89194E5
#define D4D7CDC7_8DAA_42DF_A71A_3840A89194E5
#include <complex>
#include <vector>
#include <Eigen/Dense>

namespace plasma {

/**
 * @brief A struct used to store the results of a CFAR detection
 *
 * TODO: This struct currently only supports vector inputs to detect()
 *
 */
struct DetectionReport {
  /**
   * @brief A logical matrix indicating whether a target was detected in each
   * range bin at each time instance
   *
   */
  Eigen::Array<bool, Eigen::Dynamic, Eigen::Dynamic> detections;
  /**
   * @brief A vector of the range bin indices of each detection
   *
   */
  Eigen::Array<size_t, Eigen::Dynamic, 2> indices;
  /**
   * @brief A vector of the computed CFAR threshold at each range bin
   *
   */
  Eigen::MatrixXd threshold;
};

/**
 * @brief Constant False Alarm Rate (CFAR) detector object
 *
 * TODO: Currently only implements cell-averaging CFAR.
 * TODO: Currently only supports 1D CFAR.
 *
 */
class CFARDetector {
public:
  /**
   * @brief Construct a new CFARDetector object
   *
   */
  CFARDetector() = default;
  /**
   * @brief Construct a new CFARDetector object
   *
   * @param cfar CFARDetector object
   */
  CFARDetector(const CFARDetector &cfar) = default;
  /**
   * @brief Construct a new CFARDetector object
   *
   * @param num_train Number of training cells
   * @param num_guard Number of guard cells
   * @param pfa Probability of false alarm
   */
  CFARDetector(size_t num_train, size_t num_guard, double pfa);

  /**
   * @brief Perform CFAR detection on the entire input signal
   *
   * @param x An M x 1 matrix of real-valued input data.
   * @return std::vector<bool>
   */
  DetectionReport detect(const Eigen::MatrixXd &x);

  /**
   * @brief Perform CFAR detection on the specified elements of the input data
   *
   * TODO: Currently only supports vector inputs
   *
   * @param x M x N matrix of real-valued input data, where M is the number of
   * range bins and N is the number of time instances in the input signal.
   * @param cut_index Zero-indexed index of the current cell under test (CUT)
   * @return std::vector<bool> N-vector containing logical detection
   * results for each time instance, where N is the number of rows in x
   */
  void detect(const Eigen::MatrixXd &x, size_t cut_index,
              DetectionReport &result);

protected:
  /**
   * @brief Number of guard cells on either side of the cell under test
   *
   */
  size_t d_num_guard_cells;
  /**
   * @brief Number of training cells on either side of the cell under test
   *
   */
  size_t d_num_train_cells;
  /**
   * @brief Probability of false alarm
   *
   */
  double d_pfa;
};

} // namespace plasma
#endif /* D4D7CDC7_8DAA_42DF_A71A_3840A89194E5 */