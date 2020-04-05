#pragma once

#include <vector>
#include <string>

#include "symbol.hpp"

class TextRecognizer {
public:
    TextRecognizer(Img&& img, std::vector<Symbol>&& ideals) noexcept;
    std::string GetText() const noexcept;
    
private:
    struct GraphPos {
        size_t table;
        size_t symbol;
    };
    
    struct Node {
        size_t loss;
        GraphPos prev_node;
    };
    
    using Table = std::vector<Node>;
    using Graph = std::vector<Table>;
    
    Graph GetTextsGraph() const noexcept;
    Table GetFirstTextsGraphTable() const noexcept;
    Table GetTextsGraphTable(const Graph& graph, size_t img_row) const noexcept;
    size_t CompareImgWithIdeal(size_t img_row, const Symbol& symbol) const noexcept;
    Node GetBestPredecessor(const Graph& graph, size_t table) const noexcept;
    size_t GetPredecessorLoss(const Graph& graph, size_t table, size_t pos) const noexcept;
    
    std::string GetText(const Graph& graph) const noexcept;
    
private:
    Img _img;
    std::vector<Symbol> _ideals;
};