#include <cstddef>
#include <utility>
#include <string>
#include <string_view>
#include <vector>

#include "demo.pb.h"

#include "benchmark/benchmark.h"
#include "glog/logging.h"

namespace {
    std::vector<std::pair<std::string, std::string>>
    potus({{"George Washington", "John Adams"},
           {"John Adams", "Thomas Jefferson"},
           {"Thomas Jefferson", "Aaron Burr"},
           {"James Madison", "George Clinton"},
           {"James Monroe", "Daniel Tompkins"},
           {"John Quincy Adams", "John C. Calhoun"},
           {"Andrew Jackson", "John C. Calhoun"},
           {"Martin Van Buren", "Richard M. Johnson"},
           {"William Henry Harrison", "John Tyler"},
           {"John Tyler", ""},
           {"James K. Polk", "George M. Dallas"},
           {"Zachary Taylor", "Millard Fillmore"},
           {"Millard Fillmore", ""},
           {"Franklin Pierce", "William R. King"},
           {"James Buchanan", "John C. Breckenridge"},
           {"Abraham Lincoln", "Hannibal Hamlin"}});
}

// Serialize a protobuf message that is isomorphic on the wire with map<string,
// string> but without having to copy strings into the protobuf. Runs in 800ns
// on a 8th-gen Core CPU.
void BM_SerializeMap(benchmark::State &state) {
  const std::size_t kBufSize = 1024;
  char buf[kBufSize];
  demo::MapLike ml;
  std::size_t l = kBufSize;
  for (auto _ : state) {
    char *b = buf;
    l = kBufSize;
    bool status = true;
    for (auto &kvp : potus) {
      ml.mutable_entry()->Clear();
      // set_allocated_foo APIs allow caller to temporarily donate object to
      // proto message. Proto takes ownership, until release_foo.
      ml.mutable_entry()->set_allocated_key(&kvp.first);
      ml.mutable_entry()->set_allocated_value(&kvp.second);

      status &= ml.SerializePartialToArray(b, l);
      b += ml.GetCachedSize();
      l -= ml.GetCachedSize();

      // Release these so they don't get deleted by Clear on the next iteration.
      ml.mutable_entry()->release_value();
      ml.mutable_entry()->release_key();
    }
    CHECK(status);
  }

  // Ensure buffer actually parses as a map<string, string> according to Hoyle.
  demo::ActualMap am;
  CHECK(am.ParsePartialFromArray(buf, kBufSize - l));
  CHECK_EQ(potus.size(), am.stuff_size());
}

BENCHMARK(BM_SerializeMap);

int main(int argc, char **argv) {
  google::InitGoogleLogging(argv[0]);
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
  benchmark::Shutdown();
  return 0;
}
