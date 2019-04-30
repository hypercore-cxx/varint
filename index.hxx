#ifndef VARINT_H
#define VARINT_H

#include <vector>

namespace Varint {
  struct Encoded {
    std::vector<uint8_t> value;
    unsigned bytes;
  };

  struct Decoded {
    unsigned value;
    unsigned bytes;
  };

  Encoded encode (unsigned value);
  Encoded encode (unsigned value, std::vector<uint8_t> buf, unsigned offset = 0);

  Decoded decode (std::vector<uint8_t> buf, unsigned offset = 0);
  
  unsigned encodingLength (unsigned value);
} // namespace Varint
#endif
