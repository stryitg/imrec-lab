#pragma once

#include <grammar.hpp>
#include <cstdint>

class recognizer {
public:
    
    using ideal = std::vector<std::vector<uint8_t>>;
    using image = std::vector<std::vector<uint8_t>>;
    
    struct rect {
        size_t x;
        size_t y;
        size_t x_;
        size_t y_;
    };
    
    struct point {
        size_t x;
        size_t y;
    };
    
    struct marking {
        rect r;
        size_t symbol;
    };
    
    struct cache {
        marking prev_a;
        marking prev_b;
        size_t cost;
    };
    
    using cache_tree = std::vector<std::vector<std::vector<
                       std::vector<std::vector<cache>>>>>;
    
    struct structure {
        std::vector<ideal> ideals;
        grammar g;
    };
    
    struct recognized {
        std::vector<std::vector<size_t>> rows;
        std::vector<point> corrections;
    };
        
    recognizer(const image& image, const structure& s);

    recognized get() const;

private:
    cache_tree get_cache_tree() const;
    void check_ideals_sizes() const;
    void compare_image_ideals_sizes() const;
    void check_ideals_sizes_eq() const;
    
    void run_cyk_algo();
    void compute_terminal_symbols_cost();
    void compute_terminal_symbols_cost(const point& p);
    size_t compute_terminal_symbol_cost(const point& p, size_t s);
    
    std::vector<rect> get_rect_partial_ordering() const;
    void compute_recognition_costs();
    void compute_recognition_cost(const rect& r);
    void compute_recognition_cost_v(const rect& r);
    void compute_recognition_cost_h(const rect& r);
    void compute_recognition_cost_r(const rect& r);

    void backprop(const rect& r, size_t s, recognized& rnized) const;

private:
    image _image;
    std::vector<ideal> _ideals;

    const size_t _size_x;
    const size_t _size_y;
    
    grammar _grammar;
    
    cache_tree _tree;
};