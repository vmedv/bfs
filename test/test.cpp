#include <bfs.h>
#include <cstddef>
#include <gen.h>
#include <string>

void bamboo_test(std::string name, std::size_t size) {
    auto g = generate_bamboo<bfs::graph, std::vector<std::size_t>>(size);
    auto seq_res = bfs::seq_bfs(g, 0);
    auto pg = generate_bamboo<bfs::pgraph, parlay::sequence<std::size_t>>(size);
    auto par_res = bfs::par_bfs(pg, 0);

    bool seq_val = true;
    bool par_val = true;
    for (auto i = 0; i < size; ++i) {
        seq_val &= seq_res[i] == i;
        par_val &= par_res[i] == i;
    }
   std::cout << "Test: " << name << "\n";
    if (seq_val) {
        std::cout << "seq: " << "\nSUCCESS\n";
    } else {
        std::cout << "seq: " << "\nFAIL\n";
    }
    if (par_val) {
        std::cout << "par: " << "\nSUCCESS\n\n";
    } else {
        std::cout << "par: " << "\nFAIL\n\n";
    }
}


void full_test(std::string name, std::size_t size) {
    auto g = generate_full<bfs::graph, std::vector<std::size_t>>(size);
    auto seq_res = bfs::seq_bfs(g, 0);
    auto pg = generate_full<bfs::pgraph, parlay::sequence<std::size_t>>(size);
    auto par_res = bfs::par_bfs(pg, 0);

    bool seq_val = true;
    bool par_val = true;
    for (auto i = 1; i < size; ++i) {
        seq_val &= seq_res[i] == 1;
        par_val &= par_res[i] == 1;
    }
   std::cout << "Test: " << name << "\n";
    if (seq_val) {
        std::cout << "seq: " << "\nSUCCESS\n";
    } else {
        std::cout << "seq: " << "\nFAIL\n";
    }
    if (par_val) {
        std::cout << "par: " << "\nSUCCESS\n\n";
    } else {
        std::cout << "par: " << "\nFAIL\n\n";
    }
}

int main() {
    bamboo_test("small bamboo", 10);
    bamboo_test("big bamboo", 100000);

    full_test("small full", 10);
    full_test("big full", 10000);
}
