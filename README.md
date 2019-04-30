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
```

```c++
Encoded encode (unsigned num, std::vector<uint8_t> out, unsigned offset = 0);
Decoded decode (std::vector<uint8_t> buf, unsigned offset = 0);
```

# SEE ALSO

- This is a port of Chris Dickinson's [varint][0] implementation.
- This also references Dat Rust [varint][1] implementation.
- A quick [summary][2] of how varint encoding works.
- See this [guide][3] to efficiently encoding variable-length integers in C/C++.

[0]:https://github.com/chrisdickinson/varint
[1]:https://github.com/datrs/varinteger
[2]:https://developers.google.com/protocol-buffers/docs/encoding
[3]:https://techoverflow.net/2013/01/25/efficiently-encoding-variable-length-integers-in-cc/
