#include <iostream>
#include "Array.hpp"
#include "Square.hpp"
#include "Triangle.hpp"
#include "Octagon.hpp"

int main() {
    try {
        Array<std::shared_ptr<Figure<int>>> figures;

        std::cout << "Creating figures..." << std::endl;
        auto square = std::make_shared<Square<int>>(0, 0, 4);
        auto triangle = std::make_shared<Triangle<int>>(0, 0, 4, 0, 2, 3);
        auto octagon = std::make_shared<Octagon<int>>(0, 0, 5);

        figures.push_back(square);
        figures.push_back(triangle);
        figures.push_back(octagon);

        std::cout << "\nPrinting all figures:" << std::endl;
        for (size_t i = 0; i < figures.getSize(); ++i) {
            std::cout << "Figure " << i + 1 << ":" << std::endl;
            figures[i]->printVertices();
            figures[i]->printCenter();
            std::cout << "Area: " << static_cast<double>(*figures[i]) << std::endl;
            std::cout << std::endl;
        }

        std::cout << "Total area of all figures: ";
        double total_area = 0.0;
        for (size_t i = 0; i < figures.getSize(); ++i) {
            total_area += static_cast<double>(*figures[i]);
        }
        std::cout << total_area << std::endl;

        std::cout << "\nRemoving figure at index 1 (triangle)..." << std::endl;
        figures.remove(1);

        std::cout << "\nPrinting remaining figures:" << std::endl;
        for (size_t i = 0; i < figures.getSize(); ++i) {
            std::cout << "Figure " << i + 1 << ":" << std::endl;
            figures[i]->printVertices();
            figures[i]->printCenter();
            std::cout << "Area: " << static_cast<double>(*figures[i]) << std::endl;
            std::cout << std::endl;
        }

        std::cout << "Total area of remaining figures: ";
        total_area = 0.0;
        for (size_t i = 0; i < figures.getSize(); ++i) {
            total_area += static_cast<double>(*figures[i]);
        }
        std::cout << total_area << std::endl;

        std::cout << "\nTesting with derived type Square<int> array:" << std::endl;
        Array<Square<int>> squares;
        squares.push_back(Square<int>(1, 1, 2));
        squares.push_back(Square<int>(3, 3, 5));
        for (size_t i = 0; i < squares.getSize(); ++i) {
            std::cout << "Square " << i + 1 << " area: " << static_cast<double>(squares[i]) << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
