#include "../include/Bull.h"
#include "../include/Toad.h"
#include "../include/Dragon.h"
#include "../include/npc.h"

Bull::Bull(std::string& name, int x, int y) : NPC(BullType, name, x, y) {}
Bull::Bull(std::istream &is) : NPC(BullType, is) {}
void Bull::print()
{
    std::cout << *this;
}

bool Bull::accept(std::shared_ptr<NPC> attacker) {
    FightVisitor visitor(attacker);
    return visitor.visit(std::make_shared<Bull>(*this));
}

void Bull::save(std::ostream &os)
{
    os << "bull ";
    NPC::save(os);
}

bool Bull::fight(std::shared_ptr<Toad> other)
{
    fight_notify(other, true);
    return true;
}

bool Bull::fight(std::shared_ptr<Dragon> other)
{
    fight_notify(other, false);
    return false;
}

bool Bull::fight(std::shared_ptr<Bull> other)
{
    fight_notify(other, false);
    return false;
}

std::ostream &operator<<(std::ostream &os, Bull &bull)
{
    os << "bull: " << *static_cast<NPC *>(&bull) << std::endl;
    return os;
}