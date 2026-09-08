class Logger {
public:
    Logger() { std::cout << "Logger ready\n"; }
};

class Database {
public:
    Database() { std::cout << "Database ready\n"; }
};

class Service {
    Logger& log;   // Агрегация (ссылкой)
    Database* db;  // Агрегация (указателем)
public:
    Service(Logger& l, Database* d) : log(l), db(d) {
        std::cout << "Service uses existing parts\n";
    }
};

int main() {
    Logger logger;    // создается первым
    Database db;      // создается вторым
    Service svc(logger, &db); // Service использует готовые части
}
// Вывод: Logger ready, Database ready, Service uses existing parts