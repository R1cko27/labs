//Агрегация — отношение «часть-целое», где часть может существовать отдельно от целого.
//Целое содержит ссылку или указатель на часть, не управляя её временем жизни.

class Player {
public:
    std::string name;
    Player(std::string n) : name(n) {}
};

class Team {
private:
    std::vector<Player*> players; // Агрегация через указатели
public:
    void addPlayer(Player* p) { players.push_back(p); }
};

int main() {
    Player p1("Alice");
    Player p2("Bob");
    Team team;
    team.addPlayer(&p1);
    team.addPlayer(&p2);
    // p1 и p2 существуют независимо от team
}