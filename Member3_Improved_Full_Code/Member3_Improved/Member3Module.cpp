#include "Member3Module.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

Money rupeesToPaise(long long rupees) {
    if (rupees < 0) throw std::invalid_argument("Amount cannot be negative.");
    if (rupees > std::numeric_limits<Money>::max() / 100)
        throw std::overflow_error("Amount is too large.");
    return rupees * 100;
}

std::string formatMoney(Money paise) {
    std::ostringstream out;
    const bool negative = paise < 0;
    unsigned long long absoluteValue =
        negative ? static_cast<unsigned long long>(-(paise + 1)) + 1
                 : static_cast<unsigned long long>(paise);
    if (negative) out << "-";
    out << "Rs " << absoluteValue / 100 << "."
        << std::setw(2) << std::setfill('0') << absoluteValue % 100;
    return out.str();
}

Market::Market() {
    addStock({"RELIANCE", "Reliance Industries", rupeesToPaise(1450), 2.1});
    addStock({"TCS", "Tata Consultancy Services", rupeesToPaise(3200), -0.8});
    addStock({"INFY", "Infosys", rupeesToPaise(1800), 1.4});
    addStock({"HDFC", "HDFC Bank", rupeesToPaise(1650), 0.6});
    addStock({"ITC", "ITC Limited", rupeesToPaise(450), -0.3});
}

bool Market::addStock(const Stock& stock) {
    if (stock.symbol.empty() || stock.companyName.empty() || stock.currentPrice <= 0)
        return false;
    stocks[stock.symbol] = stock;
    return true;
}

const Stock* Market::findStock(const std::string& symbol) const {
    auto it = stocks.find(symbol);
    return it == stocks.end() ? nullptr : &it->second;
}

void Market::display() const {
    std::cout << "\n========== SIMULATED MARKET ==========\n";
    std::cout << std::left << std::setw(12) << "SYMBOL"
              << std::setw(32) << "COMPANY"
              << std::right << std::setw(14) << "PRICE"
              << std::setw(12) << "CHANGE\n";
    for (const auto& entry : stocks) {
        const Stock& s = entry.second;
        std::cout << std::left << std::setw(12) << s.symbol
                  << std::setw(32) << s.companyName
                  << std::right << std::setw(14) << formatMoney(s.currentPrice)
                  << std::setw(10) << std::fixed << std::setprecision(1)
                  << s.changePercent << "%\n";
    }
}

Portfolio::Portfolio(int userId) : ownerId(userId) {}

int Portfolio::getOwnerId() const { return ownerId; }

bool Portfolio::applyExecutedTrade(const ExecutedTrade& trade, User& user,
                                   const Market& market, std::string& error) {
    if (trade.userId != ownerId || trade.userId != user.id) {
        error = "User ID does not match portfolio owner.";
        return false;
    }
    if (trade.tradeId.empty() || trade.quantity <= 0 || trade.executionPrice <= 0) {
        error = "Invalid trade ID, quantity, or execution price.";
        return false;
    }
    if (!market.findStock(trade.symbol)) {
        error = "Unknown stock symbol.";
        return false;
    }
    if (trade.side != "BUY" && trade.side != "SELL") {
        error = "Side must be BUY or SELL.";
        return false;
    }
    if (trade.executionPrice > std::numeric_limits<Money>::max() / trade.quantity) {
        error = "Trade value overflow.";
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
            holdings.emplace(trade.symbol,
                Holding{trade.symbol, trade.quantity, trade.executionPrice});
        } else {
            Holding& h = it->second;
            const long long oldQty = h.quantity;
            const long long newQty = oldQty + trade.quantity;
            if (newQty > std::numeric_limits<int>::max()) {
                error = "Holding quantity overflow.";
                return false;
            }
            const long double totalCost =
                static_cast<long double>(h.averageBuyPrice) * oldQty + tradeValue;
            h.averageBuyPrice = static_cast<Money>((totalCost + newQty / 2) / newQty);
            h.quantity = static_cast<int>(newQty);
        }
        user.cashBalance -= tradeValue;
    } else {
        auto it = holdings.find(trade.symbol);
        if (it == holdings.end() || it->second.quantity < trade.quantity) {
            error = "Insufficient shares to sell.";
            return false;
        }
        Holding& h = it->second;
        realizedPL += (trade.executionPrice - h.averageBuyPrice) * trade.quantity;
        user.cashBalance += tradeValue;
        h.quantity -= trade.quantity;
        if (h.quantity == 0) holdings.erase(it);
    }

    tradeHistory.push_back(trade);
    error.clear();
    return true;
}

Money Portfolio::holdingsValue(const Market& market) const {
    Money total = 0;
    for (const auto& entry : holdings) {
        const Stock* stock = market.findStock(entry.first);
        if (stock) total += stock->currentPrice * entry.second.quantity;
    }
    return total;
}

Money Portfolio::unrealizedPL(const Market& market) const {
    Money total = 0;
    for (const auto& entry : holdings) {
        const Holding& h = entry.second;
        const Stock* stock = market.findStock(h.symbol);
        if (stock) total += (stock->currentPrice - h.averageBuyPrice) * h.quantity;
    }
    return total;
}

Money Portfolio::totalValue(const User& user, const Market& market) const {
    return user.cashBalance + holdingsValue(market);
}

void Portfolio::display(const User& user, const Market& market) const {
    std::cout << "\n========== PORTFOLIO ==========\n"
              << "User: " << user.name << " (ID " << user.id << ")\n"
              << "Cash balance: " << formatMoney(user.cashBalance) << "\n";
    for (const auto& entry : holdings) {
        const Holding& h = entry.second;
        const Stock* stock = market.findStock(h.symbol);
        if (!stock) continue;
        std::cout << h.symbol << " | Qty: " << h.quantity
                  << " | Avg buy: " << formatMoney(h.averageBuyPrice)
                  << " | Market: " << formatMoney(stock->currentPrice)
                  << " | Unrealized P/L: "
                  << formatMoney((stock->currentPrice - h.averageBuyPrice) * h.quantity)
                  << "\n";
    }
    std::cout << "Holdings value: " << formatMoney(holdingsValue(market)) << "\n"
              << "Realized P/L: " << formatMoney(realizedPL) << "\n"
              << "Unrealized P/L: " << formatMoney(unrealizedPL(market)) << "\n"
              << "Total portfolio value: " << formatMoney(totalValue(user, market)) << "\n"
              << "Executed trades: " << tradeHistory.size() << "\n";
}

// CSV format:
// USER,userId,name,cashBalancePaise,realizedPLPaise
// HOLDING,symbol,quantity,averageBuyPricePaise
// TRADE,tradeId,userId,symbol,side,quantity,executionPricePaise
bool Portfolio::saveCSV(const std::string& filename, const User& user,
                        std::string& error) const {
    if (user.id != ownerId) {
        error = "User does not own this portfolio.";
        return false;
    }
    std::ofstream out(filename);
    if (!out) {
        error = "Could not open file for writing.";
        return false;
    }
    out << "USER," << user.id << "," << user.name << ","
        << user.cashBalance << "," << realizedPL << "\n";
    for (const auto& entry : holdings) {
        const Holding& h = entry.second;
        out << "HOLDING," << h.symbol << "," << h.quantity << ","
            << h.averageBuyPrice << "\n";
    }
    for (const auto& t : tradeHistory) {
        out << "TRADE," << t.tradeId << "," << t.userId << ","
            << t.symbol << "," << t.side << "," << t.quantity << ","
            << t.executionPrice << "\n";
    }
    if (!out) {
        error = "Failed while writing portfolio file.";
        return false;
    }
    error.clear();
    return true;
}

bool Portfolio::loadCSV(const std::string& filename, User& user,
                        std::string& error) {
    if (user.id != ownerId) {
        error = "User does not own this portfolio.";
        return false;
    }
    std::ifstream in(filename);
    if (!in) {
        error = "Could not open portfolio file.";
        return false;
    }

    std::map<std::string, Holding> loadedHoldings;
    std::vector<ExecutedTrade> loadedTrades;
    Money loadedRealizedPL = 0;
    Money loadedCash = user.cashBalance;
    bool foundUser = false;
    std::string line;

    try {
        while (std::getline(in, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string type;
            std::getline(ss, type, ',');

            if (type == "USER") {
                std::string idText, name, cashText, plText;
                std::getline(ss, idText, ',');
                std::getline(ss, name, ',');
                std::getline(ss, cashText, ',');
                std::getline(ss, plText, ',');
                int id = std::stoi(idText);
                if (id != ownerId) throw std::runtime_error("CSV user ID mismatch.");
                loadedCash = std::stoll(cashText);
                loadedRealizedPL = std::stoll(plText);
                user.name = name;
                foundUser = true;
            } else if (type == "HOLDING") {
                std::string symbol, qtyText, priceText;
                std::getline(ss, symbol, ',');
                std::getline(ss, qtyText, ',');
                std::getline(ss, priceText, ',');
                int qty = std::stoi(qtyText);
                Money price = std::stoll(priceText);
                if (symbol.empty() || qty <= 0 || price <= 0)
                    throw std::runtime_error("Invalid holding row in CSV.");
                loadedHoldings[symbol] = Holding{symbol, qty, price};
            } else if (type == "TRADE") {
                ExecutedTrade t;
                std::string userIdText, qtyText, priceText;
                std::getline(ss, t.tradeId, ',');
                std::getline(ss, userIdText, ',');
                std::getline(ss, t.symbol, ',');
                std::getline(ss, t.side, ',');
                std::getline(ss, qtyText, ',');
                std::getline(ss, priceText, ',');
                t.userId = std::stoi(userIdText);
                t.quantity = std::stoi(qtyText);
                t.executionPrice = std::stoll(priceText);
                if (t.userId != ownerId || t.tradeId.empty() ||
                    t.symbol.empty() || (t.side != "BUY" && t.side != "SELL") ||
                    t.quantity <= 0 || t.executionPrice <= 0)
                    throw std::runtime_error("Invalid trade row in CSV.");
                loadedTrades.push_back(t);
            } else {
                throw std::runtime_error("Unknown CSV row type.");
            }
        }
    } catch (const std::exception& ex) {
        error = std::string("Invalid portfolio CSV: ") + ex.what();
        return false;
    }

    if (!foundUser) {
        error = "Portfolio CSV does not contain a USER row.";
        return false;
    }
    user.cashBalance = loadedCash;
    holdings.swap(loadedHoldings);
    tradeHistory.swap(loadedTrades);
    realizedPL = loadedRealizedPL;
    error.clear();
    return true;
}

User& UserManager::createUser(const std::string& name, Money initialBalance) {
    if (name.empty() || initialBalance < 0)
        throw std::invalid_argument("Invalid user name or balance.");
    const int id = nextId++;
    users.emplace(id, User{id, name, initialBalance});
    portfolios.emplace(std::piecewise_construct,
                       std::forward_as_tuple(id),
                       std::forward_as_tuple(id));
    return users.at(id);
}

User* UserManager::getUser(int id) {
    auto it = users.find(id);
    return it == users.end() ? nullptr : &it->second;
}

const User* UserManager::getUser(int id) const {
    auto it = users.find(id);
    return it == users.end() ? nullptr : &it->second;
}

Portfolio* UserManager::getPortfolio(int userId) {
    auto it = portfolios.find(userId);
    return it == portfolios.end() ? nullptr : &it->second;
}

const Portfolio* UserManager::getPortfolio(int userId) const {
    auto it = portfolios.find(userId);
    return it == portfolios.end() ? nullptr : &it->second;
}

bool UserManager::applyExecutedTrade(const ExecutedTrade& trade,
                                     const Market& market,
                                     std::string& error) {
    User* user = getUser(trade.userId);
    Portfolio* portfolio = getPortfolio(trade.userId);
    if (!user || !portfolio) {
        error = "Unknown user ID.";
        return false;
    }
    return portfolio->applyExecutedTrade(trade, *user, market, error);
}

bool UserManager::saveUserPortfolio(int userId, const std::string& filename,
                                    std::string& error) const {
    auto userIt = users.find(userId);
    auto portfolioIt = portfolios.find(userId);
    if (userIt == users.end() || portfolioIt == portfolios.end()) {
        error = "Unknown user ID.";
        return false;
    }
    return portfolioIt->second.saveCSV(filename, userIt->second, error);
}

bool UserManager::loadUserPortfolio(int userId, const std::string& filename,
                                    std::string& error) {
    User* user = getUser(userId);
    Portfolio* portfolio = getPortfolio(userId);
    if (!user || !portfolio) {
        error = "Unknown user ID.";
        return false;
    }
    return portfolio->loadCSV(filename, *user, error);
}

std::vector<int> UserManager::getUserIds() const {
    std::vector<int> ids;
    ids.reserve(users.size());
    for (const auto& entry : users) ids.push_back(entry.first);
    std::sort(ids.begin(), ids.end());
    return ids;
}
