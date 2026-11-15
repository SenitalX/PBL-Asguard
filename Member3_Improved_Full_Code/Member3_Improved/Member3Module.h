#pragma once

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

using Money = long long; // integer paise

Money rupeesToPaise(long long rupees);
std::string formatMoney(Money paise);

struct User {
    int id{};
    std::string name;
    Money cashBalance{};
};

struct Stock {
    std::string symbol;
    std::string companyName;
    Money currentPrice{};
    double changePercent{};
};

struct Holding {
    std::string symbol;
    int quantity{};
    Money averageBuyPrice{};
};

// Adapter DTO: one record for one user's side of an executed match.
// The Trade Engine integration must create one BUY and one SELL record per match.
struct ExecutedTrade {
    std::string tradeId;
    int userId{};
    std::string symbol;
    std::string side; // "BUY" or "SELL"
    int quantity{};
    Money executionPrice{}; // paise per share
};

class Market {
private:
    std::map<std::string, Stock> stocks;

public:
    Market();
    bool addStock(const Stock& stock);
    const Stock* findStock(const std::string& symbol) const;
    void display() const;
};

class Portfolio {
private:
    int ownerId;
    std::map<std::string, Holding> holdings;
    Money realizedPL{0};
    std::vector<ExecutedTrade> tradeHistory;

public:
    explicit Portfolio(int userId);

    int getOwnerId() const;
    bool applyExecutedTrade(const ExecutedTrade& trade, User& user,
                            const Market& market, std::string& error);

    Money holdingsValue(const Market& market) const;
    Money unrealizedPL(const Market& market) const;
    Money totalValue(const User& user, const Market& market) const;
    void display(const User& user, const Market& market) const;

    bool saveCSV(const std::string& filename, const User& user,
                 std::string& error) const;
    bool loadCSV(const std::string& filename, User& user,
                 std::string& error);
};

class UserManager {
private:
    std::unordered_map<int, User> users;
    std::unordered_map<int, Portfolio> portfolios;
    int nextId{1};

public:
    User& createUser(const std::string& name, Money initialBalance);
    User* getUser(int id);
    const User* getUser(int id) const;
    Portfolio* getPortfolio(int userId);
    const Portfolio* getPortfolio(int userId) const;
    bool applyExecutedTrade(const ExecutedTrade& trade, const Market& market,
                            std::string& error);
    bool saveUserPortfolio(int userId, const std::string& filename,
                           std::string& error) const;
    bool loadUserPortfolio(int userId, const std::string& filename,
                           std::string& error);
    std::vector<int> getUserIds() const;
};
