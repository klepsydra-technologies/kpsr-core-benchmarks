#include <benchmark/benchmark.h>
#include <klepsydra/core/cache_listener.h>
#include <klepsydra/core/event_emitter_middleware_provider.h>

static void BM_EventEmitter_Test(benchmark::State &state)
{
    const int poolSize = state.range(0);
    const int vectorSize(state.range(1));
    const bool initialize = state.range(2);

    std::vector<float> vf_vec(vectorSize);
    uint16_t published_count = 0;
    std::function<void(std::vector<float> &)> fx_initializerFunction;
    if (initialize) {
        fx_initializerFunction = ([vectorSize](std::vector<float> &vf_vector) {
            vf_vector.resize(vectorSize);
        });
    } else {
        fx_initializerFunction = nullptr;
    }

    kpsr::EventEmitterMiddlewareProvider<std::vector<float>> vectorProvider(nullptr,
                                                                            "vector_provider",
                                                                            poolSize,
                                                                            fx_initializerFunction,
                                                                            nullptr);
    vectorProvider.getSubscriber()->registerListener("vector listener",
                                                     [&published_count](
                                                         const std::vector<float> &event) {
                                                         published_count++;
                                                     });

    for (auto _ : state) {
        vectorProvider.getPublisher()->publish(vf_vec);
    }

    vectorProvider.getSubscriber()->removeListener("vector listener");

    state.counters["poolSz"] = poolSize;
    state.counters["vectorSz"] = vectorSize;
    state.counters["init"] = initialize;
    state.counters["pblshCnt"] = published_count;
}

BENCHMARK(BM_EventEmitter_Test)
    ->UseRealTime()
    ->ArgsProduct({{0, 16, 32, 64}, benchmark::CreateDenseRange(0, 2048, 1 << 9), {true, false}});

BENCHMARK_MAIN();
