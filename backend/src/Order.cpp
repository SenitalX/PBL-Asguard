#include "../include/Order.h"

Order::Order(
    int orderId,
    int userId,
    const std::string& symbol,
    OrderSide side,
    OrderType type,
    int quantity,
    double price
)
    : orderId(orderId),
      userId(userId),
      symbol(symbol),
      side(side),
      type(type),
      status(OrderStatus::NEW),
      quantity(quantity),
      filledQuantity(0),
      price(price)
{
}

int Order::getOrderId() const {
    return orderId;
}

int Order::getUserId() const {
    return userId;
}

std::string Order::getSymbol() const {
    return symbol;
}

OrderSide Order::getSide() const {
    return side;
}

OrderType Order::getType() const {
    return type;
}

OrderStatus Order::getStatus() const {
    return status;
}

int Order::getQuantity() const {
    return quantity;
}

int Order::getFilledQuantity() const {
    return filledQuantity;
}

double Order::getPrice() const {
    return price;
}

void Order::setStatus(OrderStatus newStatus) {
    status = newStatus;
}

void Order::setFilledQuantity(int quantity) {
    filledQuantity = quantity;
}