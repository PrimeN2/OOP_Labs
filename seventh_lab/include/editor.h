#ifndef EDITOR__H
#define EDITOR__H
#include "npc.h"
#include <memory>


void initialize_editor();

// Фабрики -----------------------------------
std::shared_ptr<NPC> factory(std::istream &is);
std::shared_ptr<NPC> factory(NpcType type, std::string& name, int x, int y);

// save array to file
void save(const set_t &array, const std::string &filename);

//load array from file
set_t load(const std::string &filename);

// print to screen
std::ostream &operator<<(std::ostream &os, const set_t &array);

set_t fight(const set_t &array, size_t distance);

//printing npcs
void print_npcs(const set_t &array);
void print_survivors(const set_t &array);

void simulate_fight(set_t &array, size_t max_fight_distance);

void generate_npcs(set_t &array, size_t count, size_t max_x, size_t max_y);

template <int grid>
void draw_grid(set_t &array, std::array<char, grid * grid> &fields, size_t step_x, size_t step_y) {
    fields.fill(0);
    for (const std::shared_ptr<NPC> &npc : array) {
        const auto [x, y] = npc->position();
        int i = x / step_x;
        int j = y / step_y;
        if (npc->is_alive()) {
            switch (npc->get_type()) {
            case DragonType:
                fields[i + grid * j] = 'D';
                break;
            case BullType:
                fields[i + grid * j] = 'B';
                break;
            case ToadType:
                fields[i + grid * j] = 'T';
                break;
            default:
                break;
            }
        }
    }
    for (int j = 0; j < grid; ++j) {
        for (int i = 0; i < grid; ++i) {
            char c = fields[i + j * grid];
            if (c != 0)
                my_print() << "[" << c << "]";
            else
                my_print() << "[ ]";
        }
        my_print() << std::endl;
    }
    my_print() << std::endl;
}
#endif // EDITOR__H