#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// Structure to track individual stock holdings
struct Holding
{
    string symbol;
    int quantity;
    double avgBuyPrice;
};

// Portfolio and Account Class
class UserPortfolio
{
private:
    int userId;
    string username;
    double cashBalance;
    unordered_map<string, Holding> holdings; // Stock Symbol -> Holding details

public:
    UserPortfolio(int id, string name, double initialCash)
    {
        userId = id;
        username = name;
        cashBalance = initialCash;
    }

    // Deposit or add cash
    void addCash(double amount)
    {
        cashBalance += amount;
        cout << "Added Rs." << amount << " to account. New Balance: Rs." << cashBalance << "\n";
    }

    // Execute a Buy trade
    bool buyStock(string symbol, int qty, double price)
    {
        double totalCost = qty * price;
        if (cashBalance < totalCost)
        {
            cout << "Transaction Failed: Insufficient cash balance!\n";
            return false;
        }

        cashBalance -= totalCost;

        // Update holdings (Average Buy Price calculation)
        if (holdings.find(symbol) != holdings.end())
        {
            Holding &h = holdings[symbol];
            double oldTotalCost = h.quantity * h.avgBuyPrice;
            h.quantity += qty;
            h.avgBuyPrice = (oldTotalCost + totalCost) / h.quantity;
        }
        else
        {
            holdings[symbol] = {symbol, qty, price};
        }

        cout << "SUCCESS: Bought " << qty << " shares of " << symbol << " at Rs." << price << "\n";
        return true;
    }

    // Execute a Sell trade
    bool sellStock(string symbol, int qty, double price)
    {
        // Check if user owns this stock and has enough quantity
        if (holdings.find(symbol) == holdings.end() || holdings[symbol].quantity < qty)
        {
            cout << "Transaction Failed: Not enough shares to sell!\n";
            return false;
        }

        Holding &h = holdings[symbol];
        h.quantity -= qty;

        double totalRevenue = qty * price;
        cashBalance += totalRevenue;

        // If all shares are sold, remove the stock from holdings map
        if (h.quantity == 0)
        {
            holdings.erase(symbol);
        }

        cout << "SUCCESS: Sold " << qty << " shares of " << symbol << " at Rs." << price << "\n";
        return true;
    }

    // Display Portfolio & P&L
    void displayPortfolio(unordered_map<string, double> &currentMarketPrices)
    {
        cout << "\n==============================\n";
        cout << " PORTFOLIO REPORT: " << username << " (ID: " << userId << ")\n";
        cout << "==============================\n";
        cout << "Cash Balance: Rs." << cashBalance << "\n\n";
        cout << "Holdings:\n";

        double totalInvestment = 0;
        double currentValue = 0;

        if (holdings.empty())
        {
            cout << " (No stocks owned yet)\n";
        }
        else
        {
            for (auto pair : holdings)
            {
                string sym = pair.first;
                Holding h = pair.second;

                double currPrice = currentMarketPrices[sym];
                double investment = h.quantity * h.avgBuyPrice;
                double value = h.quantity * currPrice;
                double pnl = value - investment;

                totalInvestment += investment;
                currentValue += value;

                cout << " - " << sym << " | Qty: " << h.quantity
                     << " | Avg: Rs." << h.avgBuyPrice
                     << " | Current: Rs." << currPrice
                     << " | P&L: Rs." << pnl << "\n";
            }
        }
        cout << "------------------------------\n";
        cout << "Total Portfolio Value: Rs." << (cashBalance + currentValue) << "\n";
        cout << "==============================\n\n";
    }
};

int main()
{
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    string name;
    double initialCash;
    cout << "Enter Your Name: ";
    cin >> name;
    cout << "Enter Initial Cash Balance (Rs.): ";
    cin >> initialCash;

    UserPortfolio user(1, name, initialCash);

    unordered_map<string, double> marketPrices = {
        {"RELIANCE", 1450.0},
        {"TCS", 3200.0},
        {"INFY", 1800.0}};

    int choice;
    do
    {
        cout << "\n--- VELOX TRADE TERMINAL ---\n";
        cout << "1. View Portfolio & P&L\n";
        cout << "2. Buy Stock\n";
        cout << "3. Sell Stock\n";
        cout << "4. Update Market Price\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            user.displayPortfolio(marketPrices);
        }
        else if (choice == 2)
        {
            string sym;
            int qty;
            double price;
            cout << "Enter Symbol (e.g. RELIANCE): ";
            cin >> sym;
            cout << "Enter Quantity: ";
            cin >> qty;
            cout << "Enter Buy Price: ";
            cin >> price;
            user.buyStock(sym, qty, price);
        }
        else if (choice == 3)
        {
            string sym;
            int qty;
            double price;
            cout << "Enter Symbol: ";
            cin >> sym;
            cout << "Enter Quantity: ";
            cin >> qty;
            cout << "Enter Sell Price: ";
            cin >> price;
            user.sellStock(sym, qty, price);
        }
        else if (choice == 4)
        {
            string sym;
            double newPrice;
            cout << "Enter Symbol to update: ";
            cin >> sym;
            cout << "Enter New Market Price: ";
            cin >> newPrice;
            marketPrices[sym] = newPrice;
            cout << "Market price updated successfully!\n";
        }
    } while (choice != 5);

    cout << "Exiting terminal. Goodbye!\n";
    return 0;
}