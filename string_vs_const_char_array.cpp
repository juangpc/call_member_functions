
#include <vector>
#include <string>

//https://quick-bench.com/q/kDywSJGZDvG7H--2UCkUgoOlvIA

static void string(benchmark::State& state)
{
    for (auto _ : state) {
    std::vector<std::string> list({"one", "two", "three"});
    benchmark::DoNotOptimize(list);
  }
}
BENCHMARK(string);


static void charPointer(benchmark::State& state)
{
    for (auto _ : state) {
    std::vector<const char*> list({"one", "two", "three"});
    benchmark::DoNotOptimize(list);
  }
}
BENCHMARK(charPointer);


