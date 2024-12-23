#pragma once

template <typename G, typename UG>
G generate_cube(std::size_t size) {
    G g(size * size * size, UG{});
    for (std::size_t a = 0; a < size; ++a) {
        for (std::size_t b = 0; b < size; ++b) {
            for (std::size_t c = 0; c < size; ++c) {
                auto &vert_list = g[a + size * b + size * size * c];
                if (a + 1 < size)
                    vert_list.push_back(a + 1 + size * b + size * size * c);
                if (b + 1 < size)
                    vert_list.push_back(a + size * (b + 1) + size * size * c);
                if (c + 1 < size)
                    vert_list.push_back(a + size * b + size * size * (c + 1));
            }
        }
    }
    return g;
}

template <typename G, typename UG>
G generate_full(std::size_t size) {
    G g(size, UG{});
    for (std::size_t a = 0; a < size; ++a) {
        for (std::size_t b = 0; b < size; ++b) {
            if (a == b) continue;
            g[a].push_back(b);
        }
    }
    return g;
}

template <typename G, typename UG>
G generate_bamboo(std::size_t size) {
    G g(size, UG{});
    for (std::size_t a = 0; a + 1 < size; ++a) {
        g[a].push_back(a + 1);
    }
    return g;
}
