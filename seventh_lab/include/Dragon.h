#pragma once
#include "npc.h"

struct Dragon : public NPC
{
    Dragon(std::string& name, int x, int y);
    Dragon(std::istream &is);

    void print() override;
    void save(std::ostream &os) override;

    bool accept(std::shared_ptr<NPC> attacker) override;
    bool fight(std::shared_ptr<Toad> other) override;
    bool fight(std::shared_ptr<Dragon> other) override;
    bool fight(std::shared_ptr<Bull> other) override;
    friend std::ostream &operator<<(std::ostream &os, Dragon &knight);

    static constexpr NPCParams PARAMS{50, 30};
    const NPCParams& params() const override { return PARAMS; }
};