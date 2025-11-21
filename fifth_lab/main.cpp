#include "list.hpp"
#include <iostream>

int main() {
    simple_memory_resource resource(16384);

    singly_linked_list<int> list(&resource);
    std::cout << "empty: " << list.empty() << "\n";
    list.push_back(42);
    list.push_back(24);
    list.push_back(12);
    std::cout << "added 42,24,12\n";

    std::cout << "data: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    singly_linked_list<ComplexData> cdata_list(&resource);
    cdata_list.push_back(ComplexData(1, 3.14, "first"));
    cdata_list.push_back(ComplexData(2, 2.71, "second"));
    std::cout << "cdata: ";
    for (auto it = cdata_list.begin(); it != cdata_list.end(); ++it) {
        std::cout << it->id << "/" << it->value << "/" << it->name << " | ";
    }
    std::cout << "\n";

    list.clear();
    std::cout << "cleared. empty: " << list.empty() << "\n";

    return 0;
}
