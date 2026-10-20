
#include "../include/Order.h"
#include "../include/OrderManager.h"
#include "../include/TradeEngine.h"
#include "../include/Trade.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

int main() {
    OrderManager manager;
    TradeEngine engine(manager);
    std::vector<Trade> trades;
    std::string message;

    // Older sell: 2 shares at Rs. 101
    Order sellA(
        10, 101, "TCS",
        OrderSide::SELL, OrderType::LIMIT,
        2, 101.0
    );

    assert(engine.processOrder(sellA, trades, message));
    assert(trades.empty());

    // Better price: 2 shares at Rs. 100
    Order sellB(
        11, 102, "TCS",
        OrderSide::SELL, OrderType::LIMIT,
        2, 100.0
    );

    assert(engine.processOrder(sellB, trades, message));
    assert(trades.empty());

    // Incoming buy: 3 shares, willing to pay up to Rs. 105
    Order buy(
        12, 103, "TCS",
        OrderSide::BUY, OrderType::LIMIT,
        3, 105.0
    );

    assert(engine.processOrder(buy, trades, message));

    // Two executions should occur.
    assert(trades.size() == 2);

    // Best price must execute first.
    assert(trades[0].getSellOrderId() == 11);
    assert(trades[0].getQuantity() == 2);
    assert(std::abs(trades[0].getPrice() - 100.0) < 1e-9);

    // Remaining quantity executes at the next best price.
    assert(trades[1].getSellOrderId() == 10);
    assert(trades[1].getQuantity() == 1);
    assert(std::abs(trades[1].getPrice() - 101.0) < 1e-9);

    // Check final stored order states.
    Order* storedBuy = manager.getOrder(12);
    Order* storedA = manager.getOrder(10);
    Order* storedB = manager.getOrder(11);

    assert(storedBuy != nullptr);
    assert(storedA != nullptr);
    assert(storedB != nullptr);

    assert(storedBuy->getStatus() == OrderStatus::FILLED);
    assert(storedA->getFilledQuantity() == 1);
    assert(storedA->getStatus() == OrderStatus::PARTIALLY_FILLED);
    assert(storedB->getFilledQuantity() == 2);
    assert(storedB->getStatus() == OrderStatus::FILLED);

    std::cout << "PASS: Price priority test\n";
    std::cout << "Trade 1: 2 shares at Rs. "
              << trades[0].getPrice() << '\n';
    std::cout << "Trade 2: 1 share at Rs. "
              << trades[1].getPrice() << '\n';

    return 0;
}
