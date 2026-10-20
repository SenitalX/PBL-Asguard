#include "../include/Order.h"
#include "../include/OrderManager.h"
#include "../include/TradeEngine.h"
#include "../include/Trade.h"

#include <cassert>
#include <cmath>
#include<iostream>
#include<vector>

int main() {
    OrderManager manager;
    TradeEngine engine(manager);

    std::vector<Trade> trades;
    std::string message;

    // Seller offers 4 shares at Rs. 100.
    Order sellOrder(
        1, 101, "TCS",
        OrderSide::SELL, OrderType::LIMIT,
        4, 100.0
    );

    assert(engine.processOrder(sellOrder, trades, message));
    assert(trades.empty());

    // Buyer wants 10 shares at Rs. 105.
    Order buyOrder(
        2, 202, "TCS",
        OrderSide::BUY, OrderType::LIMIT,
        10, 105.0
    );

    assert(engine.processOrder(buyOrder, trades, message));

    // Four shares should execute at the resting sell price.
    assert(trades.size() == 1);
    assert(trades[0].getQuantity() == 4);
    assert(std::abs(trades[0].getPrice() - 100.0) < 1e-9);
    assert(trades[0].getBuyOrderId() == 2);
    assert(trades[0].getSellOrderId() == 1);

    // Check stored order state.
    Order* storedBuy = manager.getOrder(2);
    Order* storedSell = manager.getOrder(1);

    assert(storedBuy != nullptr);
    assert(storedSell != nullptr);

    assert(storedBuy->getFilledQuantity() == 4);
    assert(storedBuy->getStatus() == OrderStatus::PARTIALLY_FILLED);

    assert(storedSell->getFilledQuantity() == 4);
    assert(storedSell->getStatus() == OrderStatus::FILLED);

    std::cout << "PASS: Partial-fill matching test\n";
    std::cout << "Executed quantity: "
              << trades[0].getQuantity() << '\n';
    std::cout << "Execution price: Rs. "
              << trades[0].getPrice() << '\n';

    return 0;
}