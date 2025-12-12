#pragma once

#include <iostream>
#include <memory>
#include <cstring>
#include <string>
#include <set>
#include <math.h>
#include <vector>

// type for npcs
struct NPC;
struct Bull;
struct Toad;
struct Dragon;
using set_t = std::set<std::shared_ptr<NPC>>;

enum NpcType
{
    Unknown = 0,
    ToadType = 1,
    DragonType = 2,
    BullType = 3
};

struct IFightObserver{
    virtual void on_fight(const std::shared_ptr<NPC> attacker,const std::shared_ptr<NPC> defender,bool win) = 0;
};

class FightVisitor {
    private:
        std::shared_ptr<NPC> attacker;
    public:
        FightVisitor(std::shared_ptr<NPC> atk) : attacker(atk) {}
        virtual ~FightVisitor() = default;
        bool visit(std::shared_ptr<Dragon> desman);
        bool visit(std::shared_ptr<Toad> bittern);
        bool visit(std::shared_ptr<Bull> bear);
};

struct NPC : public std::enable_shared_from_this<NPC>
{
    NpcType type;
    int x{0};
    int y{0};
    std::string name;
    std::vector<std::shared_ptr<IFightObserver>> observers;

    NPC(NpcType t, std::string& name, int _x, int _y);
    NPC(NpcType t, std::istream &is);

    void subscribe(std::shared_ptr<IFightObserver>observer );
    void fight_notify(const std::shared_ptr<NPC> defender,bool win);
    virtual bool is_close(const std::shared_ptr<NPC> &other, size_t distance) const;

    virtual bool accept(std::shared_ptr<NPC> attacker) = 0;
    virtual bool fight(std::shared_ptr<Bull> other) = 0;
    virtual bool fight(std::shared_ptr<Dragon> other) = 0;
    virtual bool fight(std::shared_ptr<Toad> other) = 0;
    virtual void print() = 0;

    virtual void save(std::ostream &os);

    friend std::ostream &operator<<(std::ostream &os, NPC &npc);
};