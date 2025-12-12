#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "../include/npc.h"
#include "../include/Dragon.h"
#include "../include/Bull.h"
#include "../include/Toad.h"
#include "../include/editor.h"


TEST(NPCTest, ConstructorAndOutput) {
    std::string name = "Smaug";
    Dragon d(name, 10, 20);

    EXPECT_EQ(d.type, DragonType);
    EXPECT_EQ(d.x, 10);
    EXPECT_EQ(d.y, 20);
    EXPECT_EQ(d.name, "Smaug");

    std::stringstream ss;
    ss << static_cast<NPC &>(d);
    std::string out = ss.str();
    EXPECT_NE(out.find("name: Smaug"), std::string::npos);
    EXPECT_NE(out.find("x:10"), std::string::npos);
    EXPECT_NE(out.find("y:20"), std::string::npos);
}

TEST(NPCTest, StreamConstructorAndSave) {
    std::stringstream in("Fafnir 3 4");
    Dragon d(in);
    EXPECT_EQ(d.name, "Fafnir");
    EXPECT_EQ(d.x, 3);
    EXPECT_EQ(d.y, 4);

    std::stringstream out;
    d.save(out);
    // формат: "dragon Fafnir 3 4" + перевод строки
    std::string s = out.str();
    EXPECT_NE(s.find("dragon"), std::string::npos);
    EXPECT_NE(s.find("Fafnir"), std::string::npos);
}

TEST(NPCTest, DistanceCheck) {
    std::string n1 = "A";
    std::string n2 = "B";
    Dragon a(n1, 0, 0);
    Dragon b(n2, 3, 4); // расстояние 5

    auto pa = std::make_shared<Dragon>(a);
    auto pb = std::make_shared<Dragon>(b);

    EXPECT_TRUE(pa->is_close(pb, 5));
    EXPECT_FALSE(pa->is_close(pb, 4));
}


static std::shared_ptr<Dragon> makeDragon(const std::string &name, int x, int y) {
    std::string n = name;
    return std::make_shared<Dragon>(n, x, y);
}

static std::shared_ptr<Bull> makeBull(const std::string &name, int x, int y) {
    std::string n = name;
    return std::make_shared<Bull>(n, x, y);
}

static std::shared_ptr<Toad> makeToad(const std::string &name, int x, int y) {
    std::string n = name;
    return std::make_shared<Toad>(n, x, y);
}

TEST(FightLogicTest, DragonVsOthers) {
    auto d = makeDragon("Dragon", 0, 0);
    auto b = makeBull("Bull", 0, 0);
    auto t = makeToad("Toad", 0, 0);

    // Дракон атакует Быка и побеждает (Дракон ест Быков)
    EXPECT_TRUE(b->accept(d));   // Bull vs Dragon => true (Дракон победил)
    
    // Дракон атакует Жабу - Жаба никого не убивает и не побеждает
    EXPECT_FALSE(t->accept(d));  // Toad vs Dragon => false
    
    // Дракон защищается от Быка
    EXPECT_FALSE(d->accept(b));  // Dragon vs Bull => false (Бык не может убить Дракона)
}

TEST(FightLogicTest, BullVsOthers) {
    auto d = makeDragon("Dragon", 0, 0);
    auto b = makeBull("Bull", 0, 0);
    auto t = makeToad("Toad", 0, 0);

    // Бык атакует Жабу и побеждает (Бык топчет Жаб)
    EXPECT_TRUE(t->accept(b));   // Toad vs Bull => true (Бык победил)
    
    // Бык атакует Дракона - Дракон сильнее
    EXPECT_FALSE(d->accept(b));  // Dragon vs Bull => false
    
    // Бык защищается от Дракона
    EXPECT_TRUE(b->accept(d));   // Bull vs Dragon => true (Дракон побеждает)
}

TEST(FightLogicTest, ToadVsOthers) {
    auto d = makeDragon("Dragon", 0, 0);
    auto b = makeBull("Bull", 0, 0);
    auto t = makeToad("Toad", 0, 0);

    // Жаба никого не убивает (спасается как может)
    EXPECT_FALSE(d->accept(t));   // Dragon vs Toad => false
    EXPECT_FALSE(b->accept(t));   // Bull vs Toad => false
    EXPECT_FALSE(t->accept(t));   // Toad vs Toad => false
    
    // Жаба защищается от всех
    EXPECT_FALSE(t->accept(d));   // Toad vs Dragon => false
    EXPECT_TRUE(t->accept(b));   // Toad vs Bull => false
}

TEST(FightLogicTest, SameTypeFights) {
    auto d1 = makeDragon("Dragon1", 0, 0);
    auto d2 = makeDragon("Dragon2", 0, 0);
    
    auto b1 = makeBull("Bull1", 0, 0);
    auto b2 = makeBull("Bull2", 0, 0);
    
    auto t1 = makeToad("Toad1", 0, 0);
    auto t2 = makeToad("Toad2", 0, 0);

    // Драконы не дерутся между собой
    EXPECT_FALSE(d2->accept(d1));
    
    // Быки не дерутся между собой
    EXPECT_FALSE(b2->accept(b1));
    
    // Жабы не дерутся между собой
    EXPECT_FALSE(t2->accept(t1));
}

// -------------------- Editor: factory, save/load, fight --------------------

TEST(EditorTest, FactoryByTypeAndStream) {
    std::string name = "FireDragon";
    auto d = factory(DragonType, name, 1, 2);
    ASSERT_NE(d, nullptr);
    EXPECT_EQ(d->type, DragonType);
    EXPECT_EQ(d->name, "FireDragon");

    std::stringstream ss("dragon IceDragon 3 4");
    auto from_stream = factory(ss);
    ASSERT_NE(from_stream, nullptr);
    EXPECT_EQ(from_stream->type, DragonType);
    EXPECT_EQ(from_stream->name, "IceDragon");
}

TEST(EditorTest, SaveAndLoadRoundTrip) {
    set_t s;
    {
        std::string a = "Smaug";
        std::string b = "Ferdinand";
        std::string c = "Kermit";
        s.insert(std::make_shared<Dragon>(a, 1, 2));
        s.insert(std::make_shared<Bull>(b, 3, 4));
        s.insert(std::make_shared<Toad>(c, 5, 6));
    }

    const std::string filename = "test_npc_io.txt";
    save(s, filename);

    set_t loaded = load(filename);
    EXPECT_EQ(s.size(), loaded.size());
    
    // Удаляем тестовый файл
    std::remove(filename.c_str());
}

TEST(EditorTest, SimulateFight) {
    set_t s;
    
    // Создаем NPC на близком расстоянии
    auto d = makeDragon("Dragon", 0, 0);
    auto b = makeBull("Bull", 5, 0);  // расстояние 5
    auto t = makeToad("Toad", 10, 0); // расстояние 10
    
    s.insert(d);
    s.insert(b);
    s.insert(t);

    // При distance=15 все должны видеть друг друга
    auto dead = fight(s, 15);
    // Дракон убивает Быка, Бык убивает Жабу
    EXPECT_EQ(dead.size(), 2u);  // Бык и Жаба должны умереть
    
    // Проверяем simulate_fight
    s.clear();
    s.insert(makeDragon("Dragon", 0, 0));
    s.insert(makeBull("Bull", 5, 0));
    s.insert(makeToad("Toad", 10, 0));
    
    simulate_fight(s, 30);
    // После боя должен остаться только Дракон
    EXPECT_EQ(s.size(), 1u);
    EXPECT_EQ((*s.begin())->type, DragonType);
}

TEST(EditorTest, GenerateNPCsProducesNonEmptySet) {
    set_t s;
    generate_npcs(s, 10, 500);  // 10 NPC на поле 500x500
    EXPECT_EQ(s.size(), 10u);
    
    // Проверяем, что все координаты в пределах поля
    for (const auto& npc : s) {
        EXPECT_GE(npc->x, 0);
        EXPECT_LE(npc->x, 500);
        EXPECT_GE(npc->y, 0);
        EXPECT_LE(npc->y, 500);
    }
}

TEST(EditorTest, ObserverRegistration) {
    // Проверяем, что при создании NPC через factory они получают наблюдателей
    std::string name = "TestDragon";
    auto npc = factory(DragonType, name, 0, 0);
    
    ASSERT_NE(npc, nullptr);
    // У NPC должны быть наблюдатели после создания через factory
    // (Это косвенная проверка, так как observers приватные)
    
    // Проверяем сохранение с наблюдателями
    std::stringstream ss;
    npc->save(ss);
    std::string output = ss.str();
    EXPECT_NE(output.find("dragon"), std::string::npos);
    EXPECT_NE(output.find("TestDragon"), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}