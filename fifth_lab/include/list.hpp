#pragma once

#include <new>
#include <vector>
#include <utility>
#include <cstddef>
#include <stdexcept>
#include <string>

class fixed_block_memory_resource {
protected:
    virtual void* do_allocate(std::size_t bytes, std::size_t alignment) = 0;
    virtual void do_deallocate(void* ptr, std::size_t bytes, std::size_t alignment) = 0;
    virtual bool do_is_equal(const fixed_block_memory_resource& other) const noexcept = 0;

public:
    void* allocate(std::size_t bytes, std::size_t alignment = alignof(std::max_align_t)) {
        return do_allocate(bytes, alignment);
    }

    void deallocate(void* ptr, std::size_t bytes, std::size_t alignment = alignof(std::max_align_t)) {
        do_deallocate(ptr, bytes, alignment);
    }

    bool is_equal(const fixed_block_memory_resource& other) const noexcept {
        return do_is_equal(other);
    }

    bool operator==(const fixed_block_memory_resource& other) const noexcept {
        return is_equal(other);
    }

    bool operator!=(const fixed_block_memory_resource& other) const noexcept {
        return !is_equal(other);
    }

    virtual ~fixed_block_memory_resource() = default;
};

class simple_memory_resource : public fixed_block_memory_resource {
private:
    char* block;
    std::size_t block_size;
    std::vector<std::pair<void*, std::size_t>> allocated_blocks;

    static std::size_t align_up(std::size_t size, std::size_t alignment) {
        return (size + alignment - 1) & ~(alignment - 1);
    }

public:
    simple_memory_resource(std::size_t size) : block(new char[size]), block_size(size) {}

    ~simple_memory_resource() override {
        do_deallocate_all();
        delete[] block;
    }

    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
    if (bytes == 0) return nullptr;

    const std::size_t aligned_bytes = align_up(bytes, alignment);

    std::uintptr_t start = reinterpret_cast<std::uintptr_t>(block);
    std::uintptr_t aligned_start = (start + alignment - 1) & ~(alignment - 1);
    std::size_t offset = static_cast<std::size_t>(aligned_start - start);

    while (offset + aligned_bytes <= block_size) {
        void* ptr = block + offset;

        if (reinterpret_cast<std::uintptr_t>(ptr) % alignment == 0) {
            for (const auto& block : allocated_blocks) {
                char* existing = static_cast<char*>(block.first);
                std::size_t size = block.second;
                if (!((ptr >= existing + size) || (static_cast<char*>(ptr) + aligned_bytes <= existing))) {
                    goto next; 
                }
            }

            allocated_blocks.emplace_back(ptr, bytes);
            return ptr;
        }
    next:
        offset++;
    }

    throw std::bad_alloc();
}

    void do_deallocate(void* ptr, std::size_t bytes, std::size_t) override {
        auto it = allocated_blocks.begin();
        while (it != allocated_blocks.end()) {
            if (it->first == ptr && it->second == bytes) {
                allocated_blocks.erase(it);
                return;
            }
            ++it;
        }
    }

    bool do_is_equal(const fixed_block_memory_resource& other) const noexcept override {
        return this == &other;
    }

    void do_deallocate_all() {
        allocated_blocks.clear();
    }
};

template<typename T>
class singly_linked_list {
private:
    struct Node {
        T value;
        Node* next;

        Node(const T& val, Node* n = nullptr) : value(val), next(n) {}
        Node(T&& val, Node* n = nullptr) : value(std::move(val)), next(n) {}
    };

    Node* head;
    Node* tail;
    simple_memory_resource* resource;

public:
    using value_type = T;
    using allocator_type = void;

    class iterator {
    private:
        Node* current;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator(Node* node) : current(node) {}

        reference operator*() const { return current->value; }
        pointer operator->() const { return &current->value; }

        iterator& operator++() {
            current = current->next;
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const iterator& other) const { return current == other.current; }
        bool operator!=(const iterator& other) const { return !(*this == other); }
    };

    singly_linked_list(simple_memory_resource* res) : head(nullptr), tail(nullptr), resource(res) {}

    ~singly_linked_list() {
        clear();
    }

    void push_back(const T& value) {
        Node* new_node = static_cast<Node*>(resource->allocate(sizeof(Node)));
        try {
            new (new_node) Node(value);
        } catch (...) {
            resource->deallocate(new_node, sizeof(Node));
            throw;
        }

        if (!head) {
            head = new_node;
            tail = new_node;
            new_node->next = nullptr;
        } else {
            tail->next = new_node;
            tail = new_node;
            new_node->next = nullptr;
        }
    }

    void push_back(T&& value) {
        Node* new_node = static_cast<Node*>(resource->allocate(sizeof(Node)));
        try {
            new (new_node) Node(std::move(value));  // ← теперь будет работать
        } catch (...) {
            resource->deallocate(new_node, sizeof(Node));
            throw;
        }

        if (!head) {
            head = new_node;
            tail = new_node;
            new_node->next = nullptr;
        } else {
            tail->next = new_node;
            tail = new_node;
            new_node->next = nullptr;
        }
    }

    iterator begin() { return iterator(head); }
    iterator end() { return iterator(nullptr); }

    void clear() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            current->~Node();
            resource->deallocate(current, sizeof(Node));
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }

    bool empty() const { return head == nullptr; }
};

struct ComplexData {
    int id;
    double value;
    std::string name;

    ComplexData(int i, double v, const std::string& n) : id(i), value(v), name(n) {}
};
