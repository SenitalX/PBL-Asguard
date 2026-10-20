
#include "../include/Order.h"
#include "../include/OrderManager.h"
#include "../include/TradeEngine.h"
#include "../include/Trade.h"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

int main() {
    OrderManager manager;
    TradeEngine engine(manager);
    std::vector<Trade> trades;
    std::string message;

    // Only 3 shares are available to sell at Rs. 100.
    Order sell(
        40, 401, "TCS",
        OrderSide::SELL, OrderType::LIMIT,
        3, 100.0
    );

    assert(engine.processOrder(sell, trades, message));
    assert(trades.empty());

    // Market buy requests 5 shares.
    Order buy(
        41, 402, "TCS",
        OrderSide::BUY, OrderType::MARKET,
        5, 0.0
    );

    assert(engine.processOrder(buy, trades, message));

    // Three shares execute; the remaining two are cancelled.
    assert(trades.size() == 1);
    assert(trades[0].getQuantity() == 3);
    assert(trades[0].getSellOrderId() == 40);
    assert(trades[0].getBuyOrderId() == 41);
    assert(trades[0].getPrice() == 100.0);

    Order* storedBuy = manager.getOrder(41);
    Order* storedSell = manager.getOrder(40);

    assert(storedBuy != nullptr);
    assert(storedSell != nullptr);

    assert(storedBuy->getFilledQuantity() == 3);
    assert(storedBuy->getStatus() == OrderStatus::CANCELLED);

    assert(storedSell->getFilledQuantity() == 3);
    assert(storedSell->getStatus() == OrderStatus::FILLED);

    std::cout << "PASS: Market-order partial execution test\n";
    std::cout << "Executed: 3 shares at Rs. "
              << trades[0].getPrice() << '\n';
    std::cout << "Unfilled buy quantity: 2 shares, cancelled.\n";

    return 0;
}
