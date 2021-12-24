#ifndef AC67322C_687F_4BDC_8C4E_DD736C14C511
#define AC67322C_687F_4BDC_8C4E_DD736C14C511

#include <algorithm>
#include <complex>
#include <vector>
namespace plasma {
/**
 * @brief Compute the complex conjugate of each element in the input vector
 *
 *
 * @tparam T Input type
 * @param in Input data
 * @return std::vector<T> Conjugate of input
 */
template <typename T>
inline std::vector<T> conj(const std::vector<T> &in) {
  return in;
}

/**
 * @brief Compute the complex conjugate of each element in the input vector
 *
 *
 * @tparam T Input type
 * @param in Input data
 * @return std::vector<std::complex<double>> Conjugate of input
 */
template <typename T>
inline std::vector<std::complex<T>> conj(
    const std::vector<std::complex<T>> &in) {
  auto out = std::vector<std::complex<T>>(in.size());
  std::transform(in.begin(), in.end(), out.begin(),
                 [](const std::complex<T> &c) { return std::conj(c); });
  return out;
}

/**
 * @brief Element-wise absolute value of the input vector (real input)
 *
 * @tparam T
 * @param in
 * @return std::vector<T>
 */
template <typename T>
inline std::vector<T> abs(const std::vector<T> &in) {
  auto out = std::vector<T>(in.size());
  std::transform(in.begin(), in.end(), out.begin(),
                 [](const T &x) { return std::abs(x); });
  return out;
}

/**
 * @brief Element-wise absolute value of the input vector (complex input)
 *
 * @tparam T
 * @param in
 * @return std::vector<T>
 */
template <typename T>
inline std::vector<T> abs(const std::vector<std::complex<T>> &in) {
  auto out = std::vector<T>(in.size());
  std::transform(in.begin(), in.end(), out.begin(),
                 [](const std::complex<T> &x) { return std::abs(x); });
  return out;
}

/**
 * @brief Extract the real part of each element of the input vector
 *
 * @tparam T
 * @param in
 * @return std::vector<std::complex<T>>
 */
template <typename T>
inline std::vector<T> real(const std::vector<std::complex<T>> &in) {
  auto out = std::vector<T>(in.size());
  std::transform(in.begin(), in.end(), out.begin(),
                 [](const std::complex<T> &x) { return std::real(x); });
  return out;
}

/**
 * @brief Extract the imaginary part of each element of the input vector
 *
 * @tparam T
 * @param in
 * @return std::vector<std::complex<T>>
 */
template <typename T>
inline std::vector<T> imag(const std::vector<std::complex<T>> &in) {
  auto out = std::vector<T>(in.size());
  std::transform(in.begin(), in.end(), out.begin(),
                 [](const std::complex<T> &x) { return std::imag(x); });
  return out;
}

/**
 * @brief Convert the input vector from linear scale to db
 *
 * TODO: Add a parameter for power vs voltage quantities
 *
 * @tparam T Element type of the input vector
 * @param in Input data
 * @return std::vector<T> Output data
 */
template <typename T>
inline std::vector<T> db(std::vector<T> &in) {
  auto out = in;
  std::transform(out.begin(), out.end(), out.begin(),
                 [](T &x) { return 10 * log10(x); });
  return out;
}
}  // namespace plasma

#endif /* AC67322C_687F_4BDC_8C4E_DD736C14C511 */