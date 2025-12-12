#pragma once
#include "npc.h"

struct Toad : public NPC
{
    Toad(std::string& name, int x, int y);
    Toad(std::istream &is);

    void print() override;
    void save(std::ostream &os) override;

    bool accept(std::shared_ptr<NPC> attacker) override;
    bool fight(std::shared_ptr<Toad> other) override;
    bool fight(std::shared_ptr<Dragon> other) override;
    bool fight(std::shared_ptr<Bull> other) override;
    friend std::ostream &operator<<(std::ostream &os, Toad &knight);

    static constexpr NPCParams PARAMS{1, 10};
    const NPCParams& params() const override { return PARAMS; }
};