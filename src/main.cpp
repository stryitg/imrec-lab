#include <iostream>
#include <fstream>
#include <random>

#include "text_recognizer.hpp"

Img ReadImageFile(const std::string& file_name);
Symbol ReadSymbolFile(const std::string& file_name);
Img ReadImage(std::ifstream& file);

void ObscureImage(Img& img, double prob) noexcept;

int main() {
    auto img = ReadImageFile("../img.txt");
    auto symbol1 = ReadSymbolFile("../L.txt");
    auto symbol2 = ReadSymbolFile("../A.txt");
    auto symbol3 = ReadSymbolFile("../_.txt");
    ObscureImage(img, 0.3);
    
    std::vector<Symbol> symbols = {symbol1, symbol2, symbol3};
    TextRecognizer recognizer(std::move(img), std::move(symbols));
    
    std::cout << recognizer.GetText() << std::endl;
    return 0;
}

Img ReadImageFile(const std::string& file_name) {
    std::ifstream file(file_name);
    if(!file.is_open()) {
        throw std::runtime_error("Couldn't open file: " + file_name);
    }
    auto img = ReadImage(file);
    file.close();
    return img;
}

Symbol ReadSymbolFile(const std::string& file_name) {
    std::ifstream file(file_name);
    if(!file.is_open()) {
        throw std::runtime_error("Couldn't open file: " + file_name);
    }
    char symbol;
    file >> symbol;
    auto img = ReadImage(file);
    file.close();
    return Symbol(std::move(img), symbol);
}

Img ReadImage(std::ifstream& file) {
    size_t hight, width;
    file >> hight >> width;
    Img img(width, hight); // reading transposed
    for(size_t i = 0; i < hight; ++i) {
        for(size_t j = 0; j < width; ++j) {
            size_t val;
            file >> val;
            img(j, i) = val;
        }
    }
    
    return img;
}

void ObscureImage(Img& img, double prob) noexcept {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0,1.0);
    
    for(size_t i = 0; i < img.GetHight(); ++i) {
        for(size_t j = 0; j < img.GetWidth(); ++j) {
            const auto val = dist(gen);
            if(val < prob)
                img(i, j) = !img(i, j);
        }
    }
}
