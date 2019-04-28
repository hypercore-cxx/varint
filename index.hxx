#ifndef VARINT_H
#define VARINT_H

#include <vector>

namespace Varint {
  struct Encoded {
    std::vector<uint8_t> value;
    unsigned bytes;
  };

  struct Decoded {
    double value;
    unsigned bytes;
  };

  Encoded encode (size_t num, std::vector<uint8_t> out, unsigned offset = 0);
  Decoded decode (std::vector<uint8_t> buf, unsigned offset = 0);
} // namespace Varint
#endif
