#include <cmath>
#include <vector>

#include "index.hxx"
#include <iostream>

namespace Hyper {
  namespace Util {
    namespace Varint {
      Encoded encode (unsigned value, std::vector<uint8_t> buf, unsigned offset) {
        if (buf.empty()) {
          buf.resize(1);
        }

        unsigned _offset = offset;
        unsigned size = buf.size();

        while (value > 127U) {
          auto val = static_cast<uint8_t>(value | 128U);
          buf.emplace(buf.begin() + _offset, val);
          _offset += 1;
          value >>= 7U;
          size += _offset;
        }

        buf[_offset] = static_cast<uint8_t>(value);

        Encoded enc;
        enc.value = buf;
        enc.bytes = _offset + 1 - offset;
        return enc;
      }

      Encoded encode (unsigned value) {
        std::vector<uint8_t> buf(1);
        return Hyper::Util::Varint::encode(value, buf, 0);
      }

      Decoded decode (std::vector<uint8_t> buf, unsigned offset) {
        Decoded dec = {};

        unsigned _offset = offset;
        unsigned fac = 1;

        while (true) {
          uint8_t byte = buf[_offset];

          dec.value += fac * (byte & 127U);
          fac <<= 7U;

          _offset += 1;
          dec.bytes = _offset - offset;

          if ((byte & 128U) == 0) {
            break;
          }
        }
        
        return dec;
      }
    } // namespace Varint
  } // namespace Util
} // namespace Hyper
