#include <cmath>

namespace Varint {
  auto N1 = pow(2,  7);
  auto N2 = pow(2, 14);
  auto N3 = pow(2, 21);
  auto N4 = pow(2, 28);
  auto N5 = pow(2, 35);
  auto N6 = pow(2, 42);
  auto N7 = pow(2, 49);
  auto N8 = pow(2, 56);
  auto N9 = pow(2, 63);

  unsigned encodingLength (unsigned value) {
    return (
      value < N1 ? 1
    : value < N2 ? 2
    : value < N3 ? 3
    : value < N4 ? 4
    : value < N5 ? 5
    : value < N6 ? 6
    : value < N7 ? 7
    : value < N8 ? 8
    : value < N9 ? 9
    :              10
    );
  }
} // namespace Varint
