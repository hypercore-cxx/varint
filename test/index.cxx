#include <vector>
#include <stdlib.h>
#include <math.h>
#include <exception>

#include "../deps/heapwolf/cxx-tap/index.hxx"

#include "../index.hxx"

namespace Varint = Hyper::Util::Varint;

unsigned randint (unsigned range) {
  srand (time(NULL));
  return (unsigned int) rand() % range;
}

int main() {
  using namespace TAP;
  
  Test t;

  t.test("sanity", [](auto t) {
    t->ok(true, "true is true");
    t->end();
  });

  t.test("single byte works as expected", [](auto t) {
    std::vector<uint8_t> buf(2);
    buf[0] = 172u;
    buf[1] = 2u;
    auto data = Varint::decode(buf);
    t->equal(data.value, 300u, "should equal 300");
    t->equal(data.bytes, 2u);
    t->end();
  });

  t.test("fuzz test", [](auto t) {
    for (size_t i = 0, len = 2; i < len; ++i) {

      auto value = randint(0x7FFFFFFF);
      std::vector<uint8_t> buf;

      t->comment("encoding " + std::to_string((int) value));

      auto encoded = Varint::encode(value, buf);
      auto decoded = Varint::decode(encoded.value);

      t->comment("decoding " + std::to_string((int) decoded.value));

      t->equal((unsigned) value, (unsigned) decoded.value);
      t->equal(decoded.bytes, encoded.bytes);
    }

    t->end();
  });

  t.test("test encode works as expected", [](auto t) {
    std::vector<uint8_t> input = { 0xAC, 0x02 };
    std::vector<uint8_t> output;

    auto enc = Varint::encode(300u, input);

    t->equal(enc.value[0], 172);
    t->equal(enc.value[1], 2);
    t->end();
  });

  t.test("test decode single bytes", [](auto t) {
    auto expected = randint(127);
    std::vector<uint8_t> buf(1);
    buf[0] = expected;
    auto data = Varint::decode(buf);

    t->equal(data.value, expected);
    t->equal(data.bytes, 1);
    t->end();
  });

  t.test("test decode multiple bytes with zero", [](auto t) {
    auto expected = randint(127);
    std::vector<uint8_t> buf(2);
    buf[0] = 128;
    buf[1] = expected;
    auto data = Varint::decode(buf);
    t->equal(data.value, expected << 7);
    t->equal(data.bytes, 2);
    t->end();
  });

  t.test("encode single byte", [](auto t) {
    auto expected = randint(127);
    auto encoded = Varint::encode(expected);
    t->equal(encoded.value[0], expected);
    t->equal(encoded.bytes, 1);
    t->end();
  });

  t.test("encode multiple byte with zero first byte", [](auto t) {
    auto expected = 0x0F00;
    std::vector<uint8_t> buf(2);
    auto encoded = Varint::encode(expected, buf);
    t->equal((int) encoded.value[0], 128);
    t->equal((int) encoded.value[1], 30);
    t->equal(encoded.bytes, 2);
    t->end();
  });

  t.test("big integers", [](auto t) {
    std::vector<uint8_t> bigs;

    for (auto i = 32; i <= 53; i++) {
      bigs.push_back(pow(2, i) - 1);
      bigs.push_back(pow(2, i));
    }

    for (auto& n : bigs) {
      auto data = Varint::encode(n);
      // std::cout << n << '->' << data.value << endl;
      t->equal(Varint::decode(data.value).value, n);
      t->notEqual(Varint::decode(data.value).value, n - 1);
    }

    t->end();
  });

  t.test("encodingLength", [](auto t) {

    for (auto i = 0; i <= 53; i++) {
      auto n = pow(2, i);
      auto len = Varint::encodingLength(n);
      auto value = Varint::encode(n).value;

      t->equal(value.size(), len, "encoded value size should match encodingLength()");
    }

    t->end();
  });

  t.test("fuzz test - big", [](auto t) {
    auto MAX_INTD = pow(2, 55);
    auto MAX_INT = pow(2, 31);

    for (auto i = 0, len = 100; i < len; ++i) {
      auto expect = randint(MAX_INTD - MAX_INT) + MAX_INT;
      std::vector<uint8_t> buf(1);
      auto encoded = Varint::encode(expect, buf);
      auto decoded = Varint::decode(encoded.value);
      t->equal(expect, decoded.value, "fuzz test: " + std::to_string(expect));
      t->equal(encoded.bytes, encoded.value.size());
    }

    t->end();
  });

  t.test("buffer too short", [](auto t) {

    auto encoded = Varint::encode(9812938912312);
    auto buffer = Varint::encode(encoded.bytes);

    auto l = buffer.value.size();

    auto slice = [](auto v, auto s, auto e) {
      return std::vector<uint8_t>(v.begin() + s, v.end() - e);
    };

    while(l--) {

      try {
        auto decoded = Varint::decode(slice(buffer.value, 0, l));
      } catch (std::exception& ex) {
        t->pass("exception thrown");
      }
    }

    t->end();
  });
}
