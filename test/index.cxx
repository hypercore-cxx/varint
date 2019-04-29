#include "../index.hxx"
#include "../deps/heapwolf/cxx-tap/index.hxx"

#include <vector>
#include <stdlib.h>

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
}
