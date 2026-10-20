#include "../include/TradeEngine.h"

TradeEngine::TradeEngine(OrderManager& manager)
    : orderManager(manager),
      matchingEngine(manager),
      nextTradeId(1)
{
}

bool TradeEngine::validateOrder(
    const Order& order,
    std::string& errorMessage
) {

    // Symbol must not be empty
    if (order.getSymbol().empty()) {

        errorMessage = "Stock symbol cannot be empty";

        return false;
    }

    // Quantity must be positive
    if (order.getQuantity() <= 0) {

        errorMessage = "Quantity must be greater than zero";

        return false;
    }

    // LIMIT orders must have a valid price
    if (order.getType() == OrderType::LIMIT &&
        order.getPrice() <= 0) {

        errorMessage = "Price must be greater than zero";

        return false;
    }

    errorMessage = "Order is valid";

    return true;
}

bool TradeEngine::processOrder(
    Order& order,
    std::vector<Trade>& trades,
    std::string& message
) {

    // Step 1: Validate order
    if (!validateOrder(order, message)) {
        return false;
    }

    // Step 2: Add order to OrderManager
    if (!orderManager.addOrder(order)) {

        message = "Order ID already exists";

        return false;
    }

    // Step 3: Change order status to OPEN
    orderManager.updateOrderStatus(
        order.getOrderId(),
        OrderStatus::OPEN
    );
    // Step 4: Match the incoming order.
    std::size_t previousTradeCount = trades.size();

    matchingEngine.matchOrder(order.getOrderId(), trades);

    Order* storedOrder = orderManager.getOrder(order.getOrderId());

    if (storedOrder != nullptr) {
        order.setFilledQuantity(storedOrder->getFilledQuantity());
        order.setStatus(storedOrder->getStatus());
    }

    // Market orders cannot remain on the order book.
    if (order.getType() == OrderType::MARKET &&
        order.getStatus() != OrderStatus::FILLED) {
        orderManager.updateOrderStatus(
            order.getOrderId(),
            OrderStatus::CANCELLED
        );

        order.setStatus(OrderStatus::CANCELLED);
    }

    if (trades.size() > previousTradeCount) {
        message = "Order accepted; matching trades executed";
    } else if (order.getStatus() == OrderStatus::CANCELLED) {
        message = "Market order cancelled: no complete execution available";
    } else {
        message = "Order accepted and resting in the order system";
    }

    return true;

}
