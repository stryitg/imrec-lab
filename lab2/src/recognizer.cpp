#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <limits>

#include <recognizer.hpp>


recognizer::recognizer(const recognizer::image& image, 
                       const recognizer::structure& s)
    : _image(image)
    , _ideals(s.ideals)
    , _size_y(_ideals.at(0).size())
    , _size_x(_ideals.at(0).at(0).size())
    , _grammar(s.g)
    , _tree(get_cache_tree()) {
    run_cyk_algo();
}
             
recognizer::cache_tree recognizer::get_cache_tree() const {
    check_ideals_sizes();
    const size_t tree_size_y = _image.size() / _size_y;
    const size_t tree_size_x = _image[0].size() / _size_x;

    using v1 = std::vector<cache>;
    using v2 = std::vector<v1>;
    using v3 = std::vector<v2>;
    using v4 = std::vector<v3>;
    
    const auto d = cache{.prev_a = {},
                         .prev_b = {},
                         .cost = std::numeric_limits<size_t>::max()};
    const cache_tree ct(tree_size_y, v4(tree_size_x, v3(tree_size_y,
                        v2(tree_size_x, v1(_grammar.symbols_count(), d)))));
    return ct;
}             

void recognizer::check_ideals_sizes() const {
    compare_image_ideals_sizes();
    check_ideals_sizes_eq();
}

void recognizer::compare_image_ideals_sizes() const {
    if ((_image.size() % _size_y != 0) ||
        (_image.at(0).size() % _size_x != 0) ||
        (_image.size() / _size_y != 3)) {
        throw std::logic_error("Image sizes are not devisible by ideals sizes");
    }
}

void recognizer::check_ideals_sizes_eq() const {
    const auto iter = std::find_if(_ideals.begin(), _ideals.end(),
        [this] (const auto& ideal) {
            return ideal.size() != _size_y || 
                   ideal[0].size() != _size_x;
        });
    if (iter != _ideals.end()) {
        throw std::logic_error("All ideals must have same dimensions");
    }
}             
             
void recognizer::run_cyk_algo() {
    compute_terminal_symbols_cost();
    compute_recognition_costs();
}   

void recognizer::compute_terminal_symbols_cost() {
    for (size_t i = 0; i < _tree.size(); ++i) {
        for (size_t j = 0; j < _tree[0].size(); ++j) {
            compute_terminal_symbols_cost(point{.x = j, .y = i});
        }
    }
}

void recognizer::compute_terminal_symbols_cost(const recognizer::point& p) {
    const auto t_symbols = _grammar.get_terminal_symbols();
    for (const auto s: t_symbols) {
        const auto cost = compute_terminal_symbol_cost(p, s);
        _tree[p.y][p.x][p.y][p.x][s] = cache{.prev_a = {},
                                             .prev_b = {},
                                             .cost = cost};
    }
}

size_t recognizer::compute_terminal_symbol_cost(const recognizer::point& p,
                                                size_t s) {
    size_t val = 0;
    const auto shift_y = p.y * _size_y;
    const auto shift_x = p.x * _size_x;
    for(size_t i = 0; i < _size_y; ++i) {
        for (size_t j = 0; j < _size_x; ++j) {
            val += std::abs(_ideals[s][i][j] - _image[i + shift_y][j + shift_x]);
        }
    }
    return val;
}

void recognizer::compute_recognition_costs() {
    const auto ord = get_rect_partial_ordering();
    for (const auto& rect: ord) {
        compute_recognition_cost(rect);
    }
}

std::vector<recognizer::rect> recognizer::get_rect_partial_ordering() const {
    std::vector<rect> rects;
    for (size_t sz_y = 0; sz_y < _tree.size(); ++sz_y) {
        for (size_t sz_x = 0; sz_x < _tree[0].size(); ++sz_x) {
            for (size_t i = 0; i < _tree.size() - sz_y; ++i) {
                for (size_t j = 0; j < _tree[0].size() - sz_x; ++j) {
                    const auto r = rect{.x = j, .y = i,
                                        .x_ = j + sz_x, 
                                        .y_ = i + sz_y};
                    rects.push_back(r);
                }
            }
        }
    }
    return rects;
}

void recognizer::compute_recognition_cost(const recognizer::rect&r) {
    compute_recognition_cost_v(r);
    compute_recognition_cost_h(r);
    compute_recognition_cost_r(r);
}

void recognizer::compute_recognition_cost_v(const recognizer::rect& r) {
    for (const auto& rule: _grammar.get_vertical_rules()) {
        for (size_t y = r.y; y < r.y_; ++y) {    
            auto& v = _tree[r.y][r.x][r.y_][r.x_][rule.from];
            const auto& v_into_a = _tree[r.y][r.x][y][r.x_][rule.into_a];
            const auto& v_into_b = _tree[y + 1][r.x][r.y_][r.x_][rule.into_b];
            if (v_into_a.cost == std::numeric_limits<size_t>::max() ||
                v_into_b.cost == std::numeric_limits<size_t>::max()) {
                continue;
            }
            
            if (v.cost > v_into_a.cost + v_into_b.cost) {
                v.cost = v_into_a.cost + v_into_b.cost;
                v.prev_a = marking{.r = {.x = r.x, .y = r.y,
                                         .x_ = r.x_, .y_ = y},
                                   .symbol = rule.into_a};
                v.prev_b = marking{.r = {.x = r.x, .y = y + 1,
                                         .x_ = r.x_, .y_ = r.y_},
                                   .symbol = rule.into_b};
            }
        }
    }
}

void recognizer::compute_recognition_cost_h(const recognizer::rect& r) {
    for (const auto& rule: _grammar.get_horizontal_rules()) {
        for (size_t x = r.x; x < r.x_; ++x) {
            auto& v = _tree[r.y][r.x][r.y_][r.x_][rule.from];
            const auto& v_into_a = _tree[r.y][r.x][r.y_][x][rule.into_a];
            const auto& v_into_b = _tree[r.y][x + 1][r.y_][r.x_][rule.into_b];
            if (v_into_a.cost == std::numeric_limits<size_t>::max() ||
                v_into_b.cost == std::numeric_limits<size_t>::max()) {
                continue;
            }
            if (v.cost > v_into_a.cost + v_into_b.cost) {
                v.cost = v_into_a.cost + v_into_b.cost;
                v.prev_a = marking{.r = {.x = r.x, .y = r.y,
                                         .x_ = x, .y_ = r.y_},
                                   .symbol = rule.into_a};
                v.prev_b = marking{.r = {.x = x + 1, .y = r.y,
                                         .x_ = r.x_, .y_ = r.y_},
                                   .symbol = rule.into_b};
            }
        }
    }
}

void recognizer::compute_recognition_cost_r(const recognizer::rect& r) {
    for (const auto& rule: _grammar.get_renaming_rules()) {
        auto& v = _tree[r.y][r.x][r.y_][r.x_][rule.from];
        const auto& v_into = _tree[r.y][r.x][r.y_][r.x_][rule.into];
        if (v.cost > v_into.cost) {
            v.cost = v_into.cost;
            v.prev_a = v_into.prev_a;
            v.prev_b = v_into.prev_b;
        }
    }
}

recognizer::recognized recognizer::get() const {
    const auto r = rect{.x = 0, .y = 0,
                        .x_ = _tree[0].size() - 1, .y_ = _tree.size() - 1};
    std::vector<std::vector<size_t>> v(_tree.size(),
                                       std::vector<size_t>(_tree[0].size()));
    auto rnized = recognized{.rows = std::move(v)};
    backprop(r, _grammar.get_axiom(), rnized);
    return rnized;
}

void recognizer::backprop(const rect& r, size_t s, recognized& rnized) const {
    if ((r.x_ - r.x == 0) && (r.y_ - r.y == 0)) {
        rnized.rows[r.y][r.x] = s;
    } else {
        const auto& prev_a = _tree[r.y][r.x][r.y_][r.x_][s].prev_a; 
        const auto& prev_b = _tree[r.y][r.x][r.y_][r.x_][s].prev_b;
        backprop(prev_a.r, prev_a.symbol, rnized);
        backprop(prev_b.r, prev_b.symbol, rnized);
    }
}
