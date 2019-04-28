#include <math.h>
#include <vector>

#include "index.hxx"
#include <iostream>

namespace Varint {
  unsigned MSB = 0x80; // 128
  unsigned REST = 0x7F; // 127

  unsigned MSBALL = ~REST;
  unsigned INT = pow(2, 31);

  Encoded encode (unsigned num, std::vector<uint8_t> out, unsigned offset) {
    size_t oldOffset = offset;

    while (num >= INT) {
      out[offset++] = (num & 0xFF) | MSB;
      num /= 128;
    }

    while(num & MSBALL) {
      out[offset++] = (num & 0xFF) | MSB;
      num >>= 7;
    }

    out[offset] = num | 0;
    
    Encoded enc;
    enc.bytes = offset - oldOffset + 1;
    enc.value = out;
    
    return enc;
  }

  Decoded decode (std::vector<uint8_t> buf, unsigned offset) {
    Decoded dec;
    unsigned shift = 0u;
    unsigned counter = offset;
    uint8_t b;

    do {
      b = buf[counter++];

      dec.value = shift < 28
        ? (b & REST) << shift
        : (b & REST) * pow(2, shift);

      shift += 7;
    } while (b >= MSB);
    
    dec.bytes = counter - offset;
    
    return dec;
  }
} // namespace Varint
