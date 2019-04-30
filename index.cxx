#include <cmath>
#include <vector>

#include "index.hxx"
#include <iostream>

namespace Varint {
  Encoded encode (unsigned value, std::vector<uint8_t> buf, unsigned offset) {
    if (buf.empty()) {
      buf.resize(1);
    }

    unsigned _offset = offset;
    unsigned size = buf.size();

    while (value > 127) {
      buf[_offset] = (uint8_t) value | 128;
      _offset += 1;
      value >>= 7;
      size += _offset;
      buf.resize(size);
    }

    buf[_offset] = static_cast<uint8_t>(value);

    Encoded enc;
    enc.value = buf;
    enc.bytes = _offset + 1 - offset;
    return enc;
  }

  Encoded encode (unsigned value) {
    std::vector<uint8_t> buf(1);
    return Varint::encode(value, buf);
  }

  Decoded decode (std::vector<uint8_t> buf, unsigned offset) {
    Decoded dec = {};

    unsigned _offset = offset;
    unsigned fac = 1;

    while (true) {
      uint8_t byte = buf[_offset];

      dec.value += (unsigned) fac * (byte & 127);
      fac <<= 7;

      _offset += 1;
      dec.bytes = _offset - offset;

      if ((byte & 128) == 0) {
        break;
      }
    }
    
    return dec;
  }
} // namespace Varint
