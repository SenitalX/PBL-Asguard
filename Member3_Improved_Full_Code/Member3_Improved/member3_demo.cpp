#include "Member3Module.h"
#include <iostream>

int main() {
    try {
        Market market;
        UserManager users;
        std::string error;

        User& rohit = users.createUser("Rohit", rupeesToPaise(100000));
        User& second = users.createUser("Demo User 2", rupeesToPaise(50000));

        market.display();

        ExecutedTrade buy{"TRD-001", rohit.id, "RELIANCE", "BUY", 10,
                          rupeesToPaise(1450)};
        if (!users.applyExecutedTrade(buy, market, error)) {
            std::cerr << "BUY failed: " << error << '\n';
            return 1;
        }

        ExecutedTrade sell{"TRD-002", rohit.id, "RELIANCE", "SELL", 5,
                           rupeesToPaise(1600)};
        if (!users.applyExecutedTrade(sell, market, error)) {
            std::cerr << "SELL failed: " << error << '\n';
            return 1;
        }

        ExecutedTrade otherBuy{"TRD-003", second.id, "TCS", "BUY", 2,
                               rupeesToPaise(3200)};
        if (!users.applyExecutedTrade(otherBuy, market, error)) {
            std::cerr << "Second user's BUY failed: " << error << '\n';
            return 1;
        }

        if (Portfolio* p = users.getPortfolio(rohit.id))
            p->display(rohit, market);
        if (Portfolio* p = users.getPortfolio(second.id))
            p->display(second, market);

        if (!users.saveUserPortfolio(rohit.id, "portfolio_user_1.csv", error)) {
            std::cerr << "Save failed: " << error << '\n';
            return 1;
        }
        std::cout << "\nPortfolio saved successfully.\n";

        // Demonstrate loading into the same user's portfolio.
        if (!users.loadUserPortfolio(rohit.id, "portfolio_user_1.csv", error)) {
            std::cerr << "Load failed: " << error << '\n';
            return 1;
        }
        std::cout << "Portfolio loaded successfully.\n";
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Fatal error: " << ex.what() << '\n';
        return 1;
    }
}
