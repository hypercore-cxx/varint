#ifndef HYPER_UTIL_VARINT_H
#define HYPER_UTIL_VARINT_H

#include <vector>

namespace Hyper {
  namespace Util {
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
  } // namespace Util
} // namespace Hyper

#endif
