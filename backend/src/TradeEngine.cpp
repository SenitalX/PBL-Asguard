#include "../include/TradeEngine.h"

TradeEngine::TradeEngine(OrderManager& manager)
    : orderManager(manager),
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

    order.setStatus(OrderStatus::OPEN);

    // Matching Engine will be connected later
    message = "Order accepted and placed in the order system";

    return true;
}