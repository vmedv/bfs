#include <cassert>
#include <chrono>
#include <iostream>
#include <ranges>

#include "bfs.h"
#include "gen.h"

#define BREPS 5
#define CUBE_SIZE 400

using namespace std::chrono_literals;

template <typename G, typename T, typename F>
auto abstract_bench(G const& g, F bfs_impl) -> decltype(auto) {
    auto start = std::chrono::system_clock::now();
    auto x = bfs_impl(g, 0);
    auto end = std::chrono::system_clock::now();
    return end - start;
}

void bench(std::size_t cube_size) {
    std::chrono::milliseconds seq_acc = 0ms, par_acc = 0ms;
    const auto g = generate_cube<bfs::graph, std::vector<std::size_t>>(cube_size);
    const auto pg = generate_cube<bfs::pgraph, parlay::sequence<std::size_t>>(cube_size);
    for (auto&& i : std::ranges::views::iota(1, BREPS + 1)) {
        auto seq_m = std::chrono::duration_cast<std::chrono::milliseconds>(abstract_bench<bfs::graph, std::vector<unsigned>(bfs::graph const&, std::size_t)>(g, bfs::seq_bfs));
        seq_acc += seq_m;
        auto par_m = std::chrono::duration_cast<std::chrono::milliseconds>(abstract_bench<bfs::pgraph, std::vector<unsigned>(bfs::pgraph const&, std::size_t)>(pg, bfs::par_bfs));
        par_acc += par_m;

        std::cout << std::format(
            "Run #{}\n\tsequental: {}\n\tparallel: {}\n\tacceleration: {}\n\n",
            i,
            seq_m,
            par_m,
            static_cast<double>(seq_m.count()) / par_m.count()
        );
    }
    std::cout << std::format(
        "sequental avg time: {}\nparallel avg time: {}\nparallel {} times faster than sequental",
        seq_acc / BREPS,
        par_acc / BREPS,
        static_cast<double>(seq_acc.count()) / par_acc.count()
    );
}

int main() {
    bench(CUBE_SIZE);
}
