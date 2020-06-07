#include <iostream>
#include <fstream>
#include <array>

#include <recognizer.hpp>

enum symbol : size_t {
    zero = 0,
    one,
    empty,
    zero_zero,
    zero_one,
    one_zero,
    one_one,
    empty_zero,
    zero_empty,
    empty_one,
    one_empty,
    empty_empty,
    zero_zero_zero,
    zero_zero_one,
    zero_one_zero,
    zero_one_one,
    one_zero_zero,
    one_zero_one,
    one_one_zero,
    one_one_one,
    empty_empty_empty,
    empty_empty_one,
    empty_zero_zero, 
    empty_zero_one,
    empty_one_zero,
    empty_one_one,
    zero_empty_zero,
    zero_empty_one, 
    one_empty_zero,
    one_empty_one,
    with_carriage,
    without_carriage,
    with_carriage_empty_first_row,
    without_carriage_empty_first_row,
    with_carriage_empty_second_row,
    without_carriage_empty_second_row,
    end,
    axiom, 
    first = zero,
    last = axiom + 1,
};

recognizer::image read_image_file(const std::string& file_name);
recognizer::image read_image(std::ifstream& file);

int main() {
    grammar g;
    using c_rule = grammar::concat_rule;
    using r_rule = grammar::renaming_rule;
    g
    .add_v_rule(c_rule{.from = symbol::zero_zero, .into_a = symbol::zero, .into_b = symbol::zero})
    .add_v_rule(c_rule{.from = symbol::zero_one, .into_a = symbol::zero, .into_b = symbol::one})
    .add_v_rule(c_rule{.from = symbol::one_zero, .into_a = symbol::one, .into_b = symbol::zero})
    .add_v_rule(c_rule{.from = symbol::one_one, .into_a = symbol::one, .into_b = symbol::one})
    .add_v_rule(c_rule{.from = symbol::zero_empty, .into_a = symbol::zero, .into_b = symbol::empty})
    .add_v_rule(c_rule{.from = symbol::empty_zero, .into_a = symbol::empty, .into_b = symbol::zero})
    .add_v_rule(c_rule{.from = symbol::one_empty, .into_a = symbol::one, .into_b = symbol::empty})
    .add_v_rule(c_rule{.from = symbol::empty_one, .into_a = symbol::empty, .into_b = symbol::one})
    .add_v_rule(c_rule{.from = symbol::empty_empty, .into_a = symbol::empty, .into_b = symbol::empty})
    
    .add_v_rule(c_rule{.from = symbol::empty_empty_empty, .into_a = symbol::empty_empty, .into_b = symbol::empty})
    .add_v_rule(c_rule{.from = symbol::empty_empty_one, .into_a = symbol::empty_empty, .into_b = symbol::one})
    .add_v_rule(c_rule{.from = symbol::empty_zero_zero, .into_a = symbol::empty_zero, .into_b = symbol::zero})
    .add_v_rule(c_rule{.from = symbol::empty_zero_one, .into_a = symbol::empty_zero, .into_b = symbol::one})
    .add_v_rule(c_rule{.from = symbol::empty_one_zero, .into_a = symbol::empty_one, .into_b = symbol::zero})
    .add_v_rule(c_rule{.from = symbol::empty_one_one, .into_a = symbol::empty_one, .into_b = symbol::one})
    .add_v_rule(c_rule{.from = symbol::zero_empty_zero, .into_a = symbol::zero_empty, .into_b = symbol::zero})
    .add_v_rule(c_rule{.from = symbol::zero_empty_one, .into_a = symbol::zero_empty, .into_b = symbol::one})
    .add_v_rule(c_rule{.from = symbol::one_empty_zero, .into_a = symbol::one_empty, .into_b = symbol::zero})
    .add_v_rule(c_rule{.from = symbol::one_empty_one, .into_a = symbol::one_empty, .into_b = symbol::one})
    
    .add_v_rule(c_rule{.from = symbol::zero_zero_zero, .into_a = symbol::zero_zero, .into_b = symbol::zero})
    .add_v_rule(c_rule{.from = symbol::zero_zero_one, .into_a = symbol::zero_zero, .into_b = symbol::one})
    .add_v_rule(c_rule{.from = symbol::zero_one_zero, .into_a = symbol::zero_one, .into_b = symbol::zero})
    .add_v_rule(c_rule{.from = symbol::zero_one_one, .into_a = symbol::zero_one, .into_b = symbol::one})
    .add_v_rule(c_rule{.from = symbol::one_zero_zero, .into_a = symbol::one_zero, .into_b = symbol::zero})
    .add_v_rule(c_rule{.from = symbol::one_zero_one, .into_a = symbol::one_zero, .into_b = symbol::one})
    .add_v_rule(c_rule{.from = symbol::one_one_zero, .into_a = symbol::one_one, .into_b = symbol::zero})
    .add_v_rule(c_rule{.from = symbol::one_one_one, .into_a = symbol::one_one, .into_b = symbol::one})
    
    // .add_h_rule(c_rule{.from = symbol::zero_one_one_b, .into_a = symbol::zero_one_one, .into_b = symbol::empty_empty_empty})
    // .add_h_rule(c_rule{.from = symbol::one_zero_zero_b, .into_a = symbol::one_zero_zero, .into_b = symbol::empty_empty_empty})
    // .add_h_rule(c_rule{.from = symbol::one_zero_one_b, .into_a = symbol::one_zero_one, .into_b = symbol::empty_empty_empty})
    // .add_h_rule(c_rule{.from = symbol::one_one_zero_b, .into_a = symbol::one_one_zero, .into_b = symbol::empty_empty_empty})
    // .add_h_rule(c_rule{.from = symbol::empty_zero_zero_b, .into_a = symbol::empty_zero_zero, .into_b = symbol::empty_empty_empty})
    // .add_h_rule(c_rule{.from = symbol::empty_zero_one_b, .into_a = symbol::empty_zero_one, .into_b = symbol::empty_empty_empty})
    // .add_h_rule(c_rule{.from = symbol::empty_one_zero_b, .into_a = symbol::empty_one_zero, .into_b = symbol::empty_empty_empty})
    // .add_h_rule(c_rule{.from = symbol::empty_one_one_b, .into_a = symbol::empty_one_one, .into_b = symbol::empty_empty_empty})
    // .add_h_rule(c_rule{.from = symbol::zero_empty_zero_b, .into_a = symbol::zero_empty_zero, .into_b = symbol::empty_empty_empty})
    // .add_h_rule(c_rule{.from = symbol::zero_empty_one_b, .into_a = symbol::zero_empty_one, .into_b = symbol::empty_empty_empty})
    // .add_h_rule(c_rule{.from = symbol::one_empty_one_b, .into_a = symbol::one_empty_one, .into_b = symbol::empty_empty_empty})
    // .add_h_rule(c_rule{.from = symbol::empty_empty_empty, .into_a = symbol::empty_empty_empty, .into_b = symbol::empty_empty_empty})
    
    // .add_h_rule(c_rule{.from = symbol::zero_zero_zero, .into_a = symbol::empty_empty_empty, .into_b = symbol::zero_zero_zero})
    // .add_h_rule(c_rule{.from = symbol::zero_zero_one, .into_a = symbol::empty_empty_empty, .into_b = symbol::zero_zero_one})
    // .add_h_rule(c_rule{.from = symbol::zero_one_zero, .into_a = symbol::empty_empty_empty, .into_b = symbol::zero_one_zero})
    // .add_h_rule(c_rule{.from = symbol::zero_one_one, .into_a = symbol::empty_empty_empty, .into_b = symbol::zero_one_one})
    // .add_h_rule(c_rule{.from = symbol::one_zero_zero, .into_a = symbol::empty_empty_empty, .into_b = symbol::one_zero_zero})
    // .add_h_rule(c_rule{.from = symbol::one_zero_one, .into_a = symbol::empty_empty_empty, .into_b = symbol::one_zero_one})
    // .add_h_rule(c_rule{.from = symbol::one_one_zero, .into_a = symbol::empty_empty_empty, .into_b = symbol::one_one_zero})
    // .add_h_rule(c_rule{.from = symbol::one_one_one, .into_a = symbol::empty_empty_empty, .into_b = symbol::one_one_one})
    // 
    // .add_h_rule(c_rule{.from = symbol::empty_zero_zero, .into_a = symbol::empty_empty_empty, .into_b = symbol::empty_zero_zero})
    // .add_h_rule(c_rule{.from = symbol::empty_zero_one, .into_a = symbol::empty_empty_empty, .into_b = symbol::empty_zero_one})
    // .add_h_rule(c_rule{.from = symbol::empty_one_zero, .into_a = symbol::empty_empty_empty, .into_b = symbol::empty_one_zero})
    // .add_h_rule(c_rule{.from = symbol::empty_one_one, .into_a = symbol::empty_empty_empty, .into_b = symbol::empty_one_one})
    // .add_h_rule(c_rule{.from = symbol::zero_empty_zero, .into_a = symbol::empty_empty_empty, .into_b = symbol::zero_empty_zero})
    // .add_h_rule(c_rule{.from = symbol::zero_empty_one, .into_a = symbol::empty_empty_empty, .into_b = symbol::zero_empty_one})
    // .add_h_rule(c_rule{.from = symbol::one_empty_zero, .into_a = symbol::empty_empty_empty, .into_b = symbol::one_empty_zero})
    // .add_h_rule(c_rule{.from = symbol::one_empty_one, .into_a = symbol::empty_empty_empty, .into_b = symbol::one_empty_one})

    .add_h_rule(c_rule{.from = symbol::with_carriage, .into_a = symbol::zero_one_zero, .into_b = symbol::with_carriage})
    .add_h_rule(c_rule{.from = symbol::with_carriage, .into_a = symbol::one_zero_zero, .into_b = symbol::with_carriage})
    .add_h_rule(c_rule{.from = symbol::with_carriage, .into_a = symbol::one_one_zero, .into_b = symbol::without_carriage})
    .add_h_rule(c_rule{.from = symbol::with_carriage, .into_a = symbol::one_one_one, .into_b = symbol::with_carriage})
        
    .add_h_rule(c_rule{.from = symbol::without_carriage, .into_a = symbol::zero_zero_zero, .into_b = symbol::without_carriage})
    .add_h_rule(c_rule{.from = symbol::without_carriage, .into_a = symbol::zero_zero_one, .into_b = symbol::with_carriage})
    .add_h_rule(c_rule{.from = symbol::without_carriage, .into_a = symbol::zero_one_one, .into_b = symbol::without_carriage})
    .add_h_rule(c_rule{.from = symbol::without_carriage, .into_a = symbol::one_zero_one, .into_b = symbol::without_carriage})
    .add_h_rule(c_rule{.from = symbol::without_carriage, .into_a = symbol::empty_empty_empty, .into_b = symbol::without_carriage})
    .add_h_rule(c_rule{.from = symbol::without_carriage, .into_a = symbol::without_carriage, .into_b = symbol::empty_empty_empty})
    
    .add_h_rule(c_rule{.from = symbol::end, .into_a = symbol::empty_empty_one, .into_b = symbol::with_carriage})
    .add_h_rule(c_rule{.from = symbol::end, .into_a = symbol::empty_empty_empty, .into_b = symbol::end})
    .add_h_rule(c_rule{.from = symbol::end, .into_a = symbol::end, .into_b = symbol::empty_empty_empty})
    
    .add_h_rule(c_rule{.from = symbol::with_carriage_empty_first_row,
                       .into_a = symbol::empty_one_zero, .into_b = symbol::with_carriage})
    .add_h_rule(c_rule{.from = symbol::with_carriage_empty_first_row,
                       .into_a = symbol::empty_one_zero, .into_b = symbol::with_carriage_empty_first_row})
   
    .add_h_rule(c_rule{.from = symbol::with_carriage_empty_second_row,
                       .into_a = symbol::one_empty_zero, .into_b = symbol::with_carriage})
    .add_h_rule(c_rule{.from = symbol::with_carriage_empty_second_row,
                       .into_a = symbol::one_empty_zero, .into_b = symbol::with_carriage_empty_second_row})
  
    .add_h_rule(c_rule{.from = symbol::without_carriage_empty_first_row,
                       .into_a = symbol::empty_zero_zero, .into_b = symbol::without_carriage})
    .add_h_rule(c_rule{.from = symbol::without_carriage_empty_first_row,
                       .into_a = symbol::empty_zero_zero, .into_b = symbol::without_carriage_empty_first_row})
    .add_h_rule(c_rule{.from = symbol::without_carriage_empty_first_row,
                       .into_a = symbol::empty_zero_one, .into_b = symbol::with_carriage})
    .add_h_rule(c_rule{.from = symbol::without_carriage_empty_first_row,
                       .into_a = symbol::empty_zero_one, .into_b = symbol::with_carriage_empty_first_row})
    .add_h_rule(c_rule{.from = symbol::without_carriage_empty_first_row,
                       .into_a = symbol::empty_one_one, .into_b = symbol::without_carriage})
    .add_h_rule(c_rule{.from = symbol::without_carriage_empty_first_row,
                       .into_a = symbol::empty_one_one, .into_b = symbol::without_carriage_empty_first_row})

    .add_h_rule(c_rule{.from = symbol::without_carriage_empty_second_row,
                       .into_a = symbol::zero_empty_zero, .into_b = symbol::without_carriage})
    .add_h_rule(c_rule{.from = symbol::without_carriage_empty_second_row,
                       .into_a = symbol::zero_empty_zero, .into_b = symbol::without_carriage_empty_second_row})
    .add_h_rule(c_rule{.from = symbol::without_carriage_empty_second_row,
                       .into_a = symbol::zero_empty_one, .into_b = symbol::with_carriage})
    .add_h_rule(c_rule{.from = symbol::without_carriage_empty_second_row,
                       .into_a = symbol::zero_empty_one, .into_b = symbol::with_carriage_empty_second_row})
    .add_h_rule(c_rule{.from = symbol::without_carriage_empty_second_row,
                       .into_a = symbol::one_empty_one, .into_b = symbol::without_carriage})
    .add_h_rule(c_rule{.from = symbol::without_carriage_empty_second_row,
                       .into_a = symbol::one_empty_one, .into_b = symbol::without_carriage_empty_second_row})

    .add_r_rule(r_rule{.from = symbol::with_carriage, .into = symbol::one_one_zero})
    .add_r_rule(r_rule{.from = symbol::without_carriage, .into = symbol::zero_zero_zero})
    .add_r_rule(r_rule{.from = symbol::without_carriage, .into = symbol::zero_one_one})
    .add_r_rule(r_rule{.from = symbol::without_carriage, .into = symbol::one_zero_one})
    
    .add_r_rule(r_rule{.from = symbol::axiom, .into = symbol::without_carriage})
    .add_r_rule(r_rule{.from = symbol::axiom, .into = symbol::without_carriage_empty_first_row})
    .add_r_rule(r_rule{.from = symbol::axiom, .into = symbol::without_carriage_empty_second_row})
    .add_r_rule(r_rule{.from = symbol::axiom, .into = symbol::end})
    
    .mark_as_terminal(symbol::zero)
    .mark_as_terminal(symbol::one)
    .mark_as_terminal(symbol::empty)
    
    .mark_as_axiom(symbol::axiom)
    
    .set_symbols_count(symbol::last - symbol::first);
    
    
    recognizer::image im = read_image_file("../img/img.txt");
    
    recognizer::ideal zero = read_image_file("../img/0.txt");
    recognizer::ideal one = read_image_file("../img/1.txt");
    recognizer::ideal empty = read_image_file("../img/_.txt");
    
    
    std::vector<recognizer::ideal> ideals = {zero, one, empty};
    recognizer::structure s{.ideals = std::move(ideals), .g = std::move(g)};
    
    recognizer rec(im, s);
    const auto recognized = rec.get();
    
    const std::array map = {'0', '1', '_'};
    for (const auto& row: recognized.rows) {
        for (const auto& val: row) {
            std::cout << map[val];
        }
        std::cout << std::endl;
    }
    
    return 0;
}

recognizer::image read_image_file(const std::string& file_name) {
    std::ifstream file(file_name);
    if(!file.is_open()) {
        throw std::runtime_error("Couldn't open file: " + file_name);
    }
    const auto img = read_image(file);
    file.close();
    return img;
}

recognizer::image read_image(std::ifstream& file) {
    size_t hight, width;
    file >> hight >> width;
    recognizer::image img(hight, std::vector<uint8_t>(width));
    for(size_t i = 0; i < hight; ++i) {
        for(size_t j = 0; j < width; ++j) {
            size_t val;
            file >> val;
            img[i][j] = val;
        }
    }
    return img;
}