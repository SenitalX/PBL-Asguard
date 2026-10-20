
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

    // First order to arrive: 2 shares at Rs. 100.
    Order firstSell(
        20, 201, "TCS",
        OrderSide::SELL, OrderType::LIMIT,
        2, 100.0
    );

    assert(engine.processOrder(firstSell, trades, message));

    // Second order to arrive: same price, 2 shares.
    Order secondSell(
        21, 202, "TCS",
        OrderSide::SELL, OrderType::LIMIT,
        2, 100.0
    );

    assert(engine.processOrder(secondSell, trades, message));

    // Incoming buy order needs 3 shares.
    Order buy(
        22, 203, "TCS",
        OrderSide::BUY, OrderType::LIMIT,
        3, 105.0
    );

    assert(engine.processOrder(buy, trades, message));

    assert(trades.size() == 2);

    // Earlier sell order must execute first.
    assert(trades[0].getSellOrderId() == 20);
    assert(trades[0].getQuantity() == 2);

    // Remaining quantity comes from the second sell order.
    assert(trades[1].getSellOrderId() == 21);
    assert(trades[1].getQuantity() == 1);

    assert(trades[0].getPrice() == 100.0);
    assert(trades[1].getPrice() == 100.0);

    Order* firstStored = manager.getOrder(20);
    Order* secondStored = manager.getOrder(21);

    assert(firstStored != nullptr);
    assert(secondStored != nullptr);

    assert(firstStored->getStatus() == OrderStatus::FILLED);
    assert(secondStored->getStatus() == OrderStatus::PARTIALLY_FILLED);
    assert(secondStored->getFilledQuantity() == 1);

    std::cout << "PASS: Time-priority test\n";
    std::cout << "First execution: order "
              << trades[0].getSellOrderId() << '\n';
    std::cout << "Second execution: order "
              << trades[1].getSellOrderId() << '\n';

    return 0;
}
