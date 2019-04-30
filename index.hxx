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

  Encoded encode (unsigned num);
  Encoded encode (unsigned num, std::vector<uint8_t> out, unsigned offset = 0);

  Decoded decode (std::vector<uint8_t> buf, unsigned offset = 0);
  
  unsigned encodingLength (unsigned value);
} // namespace Varint
#endif
