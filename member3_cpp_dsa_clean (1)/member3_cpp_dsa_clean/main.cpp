#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
using Money = long long; // integer paise

Money rupeesToPaise(long long rupees) {
    if (rupees < 0) throw invalid_argument("Amount cannot be negative.");
    return rupees * 100;
}

string formatMoney(Money paise) {
    ostringstream out;
    out << "Rs " << paise / 100 << "." << setw(2) << setfill('0') << paise % 100;
    return out.str();
}

struct User {
    int id;
    string name;
    Money cashBalance;
};

struct Stock {
    string symbol;
    string companyName;
    Money currentPrice;
    double changePercent;
};

struct Holding {
    string symbol;
    int quantity;
    Money averageBuyPrice;
};

struct ExecutedTrade {
    string tradeId;
    int userId;
    string symbol;
    string side;
    int quantity;
    Money executionPrice;
};

class Market {
private:
    map<string, Stock> stocks; // sorted by symbol; lookup O(log S)

public:
    Market() {
        addStock({"RELIANCE", "Reliance Industries", rupeesToPaise(1450), 2.1});
        addStock({"TCS", "Tata Consultancy Services", rupeesToPaise(3200), -0.8});
        addStock({"INFY", "Infosys", rupeesToPaise(1800), 1.4});
        addStock({"HDFC", "HDFC Bank", rupeesToPaise(1650), 0.6});
        addStock({"ITC", "ITC Limited", rupeesToPaise(450), -0.3});
    }

    bool addStock(const Stock& stock) {
        if (stock.symbol.empty() || stock.companyName.empty() || stock.currentPrice <= 0)
            return false;
        stocks[stock.symbol] = stock;
        return true;
    }

    const Stock* findStock(const string& symbol) const {
        auto it = stocks.find(symbol);
        return it == stocks.end() ? nullptr : &it->second;
    }

    void display() const {
        cout << "\n========== SIMULATED MARKET ==========\n";
        cout << left << setw(12) << "SYMBOL"
             << setw(32) << "COMPANY"
             << right << setw(14) << "PRICE"
             << setw(12) << "CHANGE" << '\n';

        for (const auto& entry : stocks) {
            const Stock& stock = entry.second;
            cout << left << setw(12) << stock.symbol
                 << setw(32) << stock.companyName
                 << right << setw(14) << formatMoney(stock.currentPrice)
                 << setw(10) << fixed << setprecision(1) << stock.changePercent << "%\n";
        }
    }
};

class Portfolio {
private:
    int ownerId;
    map<string, Holding> holdings;       // O(log H) lookup
    Money realizedPL = 0;
    vector<ExecutedTrade> tradeHistory;  // append amortized O(1)

public:
    explicit Portfolio(int userId) : ownerId(userId) {}

    // Apply only trades confirmed by the Trade Engine.
    bool applyExecutedTrade(const ExecutedTrade& trade, User& user,
                            const Market& market, string& error) {
        if (trade.userId != ownerId || trade.userId != user.id) {
            error = "User ID does not match portfolio owner.";
            return false;
        }
        if (trade.tradeId.empty() || trade.quantity <= 0 || trade.executionPrice <= 0) {
            error = "Invalid trade ID, quantity, or execution price.";
            return false;
        }
        if (market.findStock(trade.symbol) == nullptr) {
            error = "Unknown stock symbol.";
            return false;
        }

        const Money tradeValue = trade.executionPrice * trade.quantity;

        if (trade.side == "BUY") {
            if (user.cashBalance < tradeValue) {
                error = "Insufficient cash balance.";
                return false;
            }

            auto it = holdings.find(trade.symbol);
            if (it == holdings.end()) {
                holdings[trade.symbol] =
                    {trade.symbol, trade.quantity, trade.executionPrice};
            } else {
                Holding& holding = it->second;
                const long long oldQuantity = holding.quantity;
                const long long newQuantity = oldQuantity + trade.quantity;
                const Money oldCost = holding.averageBuyPrice * oldQuantity;
                holding.averageBuyPrice =
                    (oldCost + tradeValue + newQuantity / 2) / newQuantity;
                holding.quantity = static_cast<int>(newQuantity);
            }

            user.cashBalance -= tradeValue;
            tradeHistory.push_back(trade);
            error.clear();
            return true;
        }

        if (trade.side == "SELL") {
            auto it = holdings.find(trade.symbol);
            if (it == holdings.end() || it->second.quantity < trade.quantity) {
                error = "Insufficient shares to sell.";
                return false;
            }

            Holding& holding = it->second;
            realizedPL += (trade.executionPrice - holding.averageBuyPrice) * trade.quantity;
            user.cashBalance += tradeValue;
            holding.quantity -= trade.quantity;

            if (holding.quantity == 0)
                holdings.erase(it);

            tradeHistory.push_back(trade);
            error.clear();
            return true;
        }

        error = "Side must be BUY or SELL.";
        return false;
    }

    Money holdingsValue(const Market& market) const {
        Money total = 0;
        for (const auto& entry : holdings) {
            const Stock* stock = market.findStock(entry.first);
            if (stock)
                total += stock->currentPrice * entry.second.quantity;
        }
        return total;
    }

    Money unrealizedPL(const Market& market) const {
        Money total = 0;
        for (const auto& entry : holdings) {
            const Holding& holding = entry.second;
            const Stock* stock = market.findStock(holding.symbol);
            if (stock)
                total += (stock->currentPrice - holding.averageBuyPrice) * holding.quantity;
        }
        return total;
    }

    Money totalValue(const User& user, const Market& market) const {
        return user.cashBalance + holdingsValue(market);
    }

    void display(const User& user, const Market& market) const {
        cout << "\n========== PORTFOLIO ==========\n";
        cout << "User: " << user.name << " (ID " << user.id << ")\n";
        cout << "Cash balance: " << formatMoney(user.cashBalance) << "\n\n";

        cout << left << setw(12) << "SYMBOL"
             << right << setw(8) << "QTY"
             << setw(16) << "AVG BUY"
             << setw(16) << "MARKET PRICE"
             << setw(16) << "VALUE"
             << setw(18) << "UNREAL. P/L" << '\n';

        cout << string(86, '-') << '\n';

        for (const auto& entry : holdings) {
            const Holding& holding = entry.second;
            const Stock* stock = market.findStock(holding.symbol);
            if (!stock) continue;

            cout << left << setw(12) << holding.symbol
                 << right << setw(8) << holding.quantity
                 << setw(16) << formatMoney(holding.averageBuyPrice)
                 << setw(16) << formatMoney(stock->currentPrice)
                 << setw(16) << formatMoney(stock->currentPrice * holding.quantity)
                 << setw(18) << formatMoney(
                        (stock->currentPrice - holding.averageBuyPrice) * holding.quantity)
                 << '\n';
        }

        cout << string(86, '-') << '\n';
        cout << "Holdings market value : " << formatMoney(holdingsValue(market)) << '\n';
        cout << "Realized P/L          : " << formatMoney(realizedPL) << '\n';
        cout << "Unrealized P/L        : " << formatMoney(unrealizedPL(market)) << '\n';
        cout << "Total portfolio value : " << formatMoney(totalValue(user, market)) << '\n';
        cout << "Executed trades       : " << tradeHistory.size() << '\n';
    }

    bool saveCSV(const string& filename, string& error) const {
        ofstream out(filename);
        if (!out) {
            error = "Could not open file for writing.";
            return false;
        }

        out << ownerId << ',' << realizedPL << '\n';
        for (const auto& entry : holdings) {
            const Holding& holding = entry.second;
            out << holding.symbol << ',' << holding.quantity << ','
                << holding.averageBuyPrice << '\n';
        }

        if (!out) {
            error = "Failed to write portfolio file.";
            return false;
        }
        error.clear();
        return true;
    }
};

class UserManager {
private:
    unordered_map<int, User> users; // average O(1) user lookup
    int nextId = 1;

public:
    User& createUser(const string& name, Money initialBalance) {
        if (name.empty() || initialBalance < 0)
            throw invalid_argument("Invalid user name or balance.");
        const int id = nextId++;
        users.emplace(id, User{id, name, initialBalance});
        return users.at(id);
    }
};

int main() {
    try {
        Market market;
        UserManager userManager;
        User& user = userManager.createUser("Demo User", rupeesToPaise(100000));
        Portfolio portfolio(user.id);
        string error;

        cout << "============================================\n";
        cout << "       STOCK MARKET SIMULATOR\n";
        cout << "       MEMBER 3: USER + MARKET + PORTFOLIO\n";
        cout << "============================================\n";
        cout << "User ID         : " << user.id << '\n';
        cout << "Starting balance: " << formatMoney(user.cashBalance) << '\n';

        market.display();

        cout << "\n========== TRADE DEMO ==========\n";
        cout << "BUY  10 RELIANCE @ Rs 1450\n";
        ExecutedTrade buy{"TRD-001", user.id, "RELIANCE", "BUY", 10,
                          rupeesToPaise(1450)};
        if (portfolio.applyExecutedTrade(buy, user, market, error))
            cout << "BUY successful. New balance: " << formatMoney(user.cashBalance) << '\n';
        else
            cout << "BUY rejected: " << error << '\n';

        cout << "\nSELL 5 RELIANCE @ Rs 1600\n";
        ExecutedTrade sell{"TRD-002", user.id, "RELIANCE", "SELL", 5,
                           rupeesToPaise(1600)};
        if (portfolio.applyExecutedTrade(sell, user, market, error))
            cout << "SELL successful. New balance: " << formatMoney(user.cashBalance) << '\n';
        else
            cout << "SELL rejected: " << error << '\n';

        cout << "\n========== VALIDATION TEST ==========\n";
        cout << "Attempt: SELL 100 RELIANCE\n";
        ExecutedTrade invalidSell{"TRD-003", user.id, "RELIANCE", "SELL", 100,
                                  rupeesToPaise(1600)};
        if (!portfolio.applyExecutedTrade(invalidSell, user, market, error))
            cout << "Correctly rejected: " << error << '\n';
        else
            cout << "ERROR: invalid sell was accepted.\n";

        portfolio.display(user, market);

        if (portfolio.saveCSV("portfolio_demo.csv", error))
            cout << "\nPortfolio saved to portfolio_demo.csv\n";
        else
            cout << "\nSave failed: " << error << '\n';

        cout << "\nDemo completed. Prices are simulated educational data.\n";
    } catch (const exception& ex) {
        cerr << "Error: " << ex.what() << '\n';
        return 1;
    }
    return 0;
}
