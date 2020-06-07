#pragma once

#include <vector>

class grammar {
public:
    struct concat_rule {
        size_t from;
        size_t into_a;
        size_t into_b;
            
        bool operator==(const concat_rule& other) const {
            return from == other.from && into_a == other.into_a &&
                   into_b == other.into_b;
        }
    };
    
    struct renaming_rule {
        size_t from;
        size_t into;
                
        bool operator==(const renaming_rule& other) const {
            return from == other.from && into == other.into;
        }
    };
    
    grammar& add_v_rule(concat_rule rule) {
        _v_rules.push_back(rule);
        return *this;
    }
    
    grammar& add_h_rule(concat_rule rule) {
        _h_rules.push_back(rule);
        return *this;
    }
    
    grammar& add_r_rule(renaming_rule rule) {
        _r_rules.push_back(rule);
        return *this;
    }
    
    grammar& mark_as_terminal(size_t symbol) {
        _terminal_symbols.push_back(symbol);
        return *this;
    }
    
    size_t symbols_count() const {
        return _symbols_count;
    }
    
    grammar& mark_as_axiom(size_t symbol) {
        _axiom = symbol;
        return *this;
    }
    
    size_t get_axiom() const {
        return _axiom;
    }
    
    const std::vector<concat_rule>& get_horizontal_rules() const {
        return _h_rules;
    }
    
    const std::vector<concat_rule>& get_vertical_rules() const {
        return _v_rules;
    }
    
    const std::vector<renaming_rule>& get_renaming_rules() const {
        return _r_rules;
    }
    
    const std::vector<size_t>& get_terminal_symbols() const {
        return _terminal_symbols;
    }
    
    void set_symbols_count(size_t symbols_count) {
        _symbols_count = symbols_count;
    }
    
private:
    std::vector<concat_rule> _h_rules;
    std::vector<concat_rule> _v_rules;
    std::vector<renaming_rule> _r_rules;
    std::vector<size_t> _terminal_symbols; 
    size_t _axiom;
    size_t _symbols_count;
};
