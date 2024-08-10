include_directories(../src)

function (add_benchmark executableName fileName)
    add_executable(
        HashMapBenchmark
        HashMapBenchmark.cc
    )

    target_link_libraries(
        HashMapBenchmark
        benchmark::benchmark
    )
endfunction()

add_benchmark(HashMapBenchmark HashMapBenchmark.cc)