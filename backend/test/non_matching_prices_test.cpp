
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

    Order sell(
        30, 301, "TCS",
        OrderSide::SELL, OrderType::LIMIT,
        5, 110.0
    );

    assert(engine.processOrder(sell, trades, message));
    assert(trades.empty());

    Order buy(
        31, 302, "TCS",
        OrderSide::BUY, OrderType::LIMIT,
        5, 100.0
    );

    assert(engine.processOrder(buy, trades, message));

    // Incompatible prices must not produce a trade.
    assert(trades.empty());

    Order* storedSell = manager.getOrder(30);
    Order* storedBuy = manager.getOrder(31);

    assert(storedSell != nullptr);
    assert(storedBuy != nullptr);

    assert(storedSell->getFilledQuantity() == 0);
    assert(storedBuy->getFilledQuantity() == 0);

    assert(storedSell->getStatus() == OrderStatus::OPEN);
    assert(storedBuy->getStatus() == OrderStatus::OPEN);

    std::cout << "PASS: Non-matching prices test\n";
    std::cout << "No trades executed; both orders remain open.\n";

    return 0;
}
