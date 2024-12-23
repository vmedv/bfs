#pragma once

#include <vector>
#include <parlay/sequence.h>

namespace bfs {
    using graph = std::vector<std::vector<std::size_t> >;
    using pgraph = parlay::sequence<parlay::sequence<std::size_t> >;

    std::vector<unsigned> seq_bfs(graph const &g, std::size_t src);

    std::vector<unsigned> par_bfs(pgraph const &g, std::size_t src);

}
