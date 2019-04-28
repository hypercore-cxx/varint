# SYNOPSIS
Use `msb` to create integer values of varying sizes.


# USAGE
This module is designed to work with the [`datcxx`][0] build tool. To add this
module to your project us the following command...

```bash
build add heapwolf/cxx-varint
```


# TEST

```bash
build test
```


# API

```c++
struct Encoded {
  std::vector<uint8_t> value;
  unsigned bytes;
};

struct Decoded {
  unsigned value;
  unsigned bytes;
};

Encoded encode (unsigned num, std::vector<uint8_t> out, unsigned offset = 0);
Decoded decode (std::vector<uint8_t> buf, unsigned offset = 0);
```

# SEE ALSO

This is a port of Chris Dickinson's [varint][0] implementation.

[0]:https://github.com/chrisdickinson/varint
