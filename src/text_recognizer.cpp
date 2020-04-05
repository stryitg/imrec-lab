#include <limits>
#include <algorithm>

#include "text_recognizer.hpp"

TextRecognizer::TextRecognizer(Img&& img, std::vector<Symbol>&& ideals) noexcept
    : _img(std::move(img))
    , _ideals(std::move(ideals)) {}
    
std::string TextRecognizer::GetText() const noexcept {
    Graph graph = GetTextsGraph();
    return GetText(graph);
};

TextRecognizer::Graph TextRecognizer::GetTextsGraph() const noexcept {
    Graph graph(_img.GetHight(), Table(_ideals.size()));
    graph[0] = GetFirstTextsGraphTable();
    for(size_t i = 1; i < graph.size(); ++i) {
        graph[i] = GetTextsGraphTable(graph, i);
    }
    return graph;
}

TextRecognizer::Table TextRecognizer::GetFirstTextsGraphTable() const noexcept {
    Table table(_ideals.size());
    std::transform(_ideals.begin(), _ideals.end(), table.begin(),
        [this] (const auto& symbol) {
            const size_t loss = CompareImgWithIdeal(0, symbol);
            return Node{.loss = loss, .prev_node = {0, 0}};
    });
    return table;
}

TextRecognizer::Table TextRecognizer::GetTextsGraphTable(const TextRecognizer::Graph& graph, 
                                                         size_t img_row) const noexcept {
    Table table(_ideals.size());
    const auto node = GetBestPredecessor(graph, img_row);
    std::transform(_ideals.begin(), _ideals.end(), table.begin(),
        [this, img_row, &node] (const auto& symbol) {
            const size_t loss = CompareImgWithIdeal(img_row, symbol);
            return Node{.loss = loss + node.loss, .prev_node = node.prev_node};
    });
    return table;
}

size_t TextRecognizer::CompareImgWithIdeal(size_t img_row, const Symbol& symbol) const noexcept {
    if(img_row + symbol.GetHight() > _img.GetHight())
        return std::numeric_limits<size_t>::max();
    else
        return symbol.Compare(_img.GetWindow(img_row, symbol.GetHight()));
}

TextRecognizer::Node TextRecognizer::GetBestPredecessor(const TextRecognizer::Graph& graph,
                                                        size_t table) const noexcept {
    size_t min_loss = std::numeric_limits<size_t>::max();
    GraphPos best;
    for(size_t i = 0; i < _ideals.size(); ++i) {
        const size_t loss = GetPredecessorLoss(graph, table, i);
        if(loss < min_loss) {
            best = {.table = table - _ideals[i].GetHight(), .symbol = i};
            min_loss = loss;
        }
    }
    return {.loss = min_loss, .prev_node = best};
}

size_t TextRecognizer::GetPredecessorLoss(const TextRecognizer::Graph& graph, 
                                          size_t table, size_t pos) const noexcept {
    if(const size_t hight = _ideals[pos].GetHight(); table < hight)
        return std::numeric_limits<size_t>::max();
    else
        return graph[table - hight][pos].loss;
}

std::string TextRecognizer::GetText(const TextRecognizer::Graph& graph) const noexcept {
    std::string text;
    Node best_last_node = GetBestPredecessor(graph, graph.size());
    GraphPos pos = best_last_node.prev_node;
    while(pos.table != 0) {
        text = _ideals[pos.symbol].GetSymbol() + text;
        pos = graph[pos.table][pos.symbol].prev_node;
    }
    return _ideals[pos.symbol].GetSymbol() + text;
}

