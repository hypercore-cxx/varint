#include "../index.hxx"
#include "../deps/heapwolf/cxx-tap/index.hxx"

#include <vector>

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
}
