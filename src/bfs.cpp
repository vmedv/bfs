#include "bfs.h"

#include <deque>
#include <limits>

#include "parlay/sequence.h"
#include "parlay/primitives.h"

std::vector<unsigned> bfs::seq_bfs(graph const &g, std::size_t src) {
    std::vector dist(g.size(), std::numeric_limits<unsigned>::max());
    dist[src] = 0;
    std::deque<std::size_t> q;
    q.push_back(src);
    while (not q.empty()) {
        auto u = q.front();
        q.pop_front();
        for (auto const &v: g[u]) {
            if (dist[v] == std::numeric_limits<unsigned>::max()) {
                dist[v] = dist[u] + 1;
                q.push_back(v);
            }
        }
    }
    return dist;
}

std::vector<unsigned> bfs::par_bfs(pgraph const &g, std::size_t src) {
    // parlay::sequence<std::atomic_int> used(g.size(), 0);
    auto used = parlay::tabulate<std::atomic_int>(g.size(), [](auto) { return -1; });
    used[src] = 0;

    parlay::sequence frontier(1, src);
    unsigned layer = 0;
    while (not frontier.empty()) {
        layer++;
        auto degs = parlay::tabulate(frontier.size(), [&](auto i) { return g[frontier[i]].size(); });
        auto [scan, total] = parlay::scan(degs);
        parlay::sequence next_frontier(total, std::numeric_limits<std::size_t>::max());
        parlay::for_each(parlay::zip(frontier, parlay::iota(frontier.size())), [&](auto c) {
            auto [v, idx] = c;
            for (auto const &[u, loc_idx]: parlay::zip(g[v], parlay::iota(g[v].size()))) {
                if (int expected = -1; used[u].compare_exchange_strong(expected, layer)) {
                    next_frontier[scan[idx] + loc_idx] = u;
                }
            }
        });
        frontier = parlay::filter(next_frontier, [](auto x) { return x != std::numeric_limits<std::size_t>::max(); });
    }
    std::vector<unsigned> dists(g.size());
    for (std::size_t i = 0; i < used.size(); ++i) { dists[i] = used[i]; };
    return dists;
}
