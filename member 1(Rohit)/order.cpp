#include "order.h"

// Constructor: Order object ki saari details initialize karta hai
Order::Order(int orderId,
             int userId,
             string stockSymbol,
             string side,
             int quantity,
             double price,
             string timestamp,
             string orderType)
{
    this->orderId = orderId;
    this->userId = userId;
    this->stockSymbol = stockSymbol;
    this->side = side;
    this->quantity = quantity;
    this->price = price;
    this->timestamp = timestamp;
    this->orderType = orderType;
}

// Order ki unique ID return karega
int Order::getOrderId()
{
    return orderId;
}

// User ID return karega
int Order::getUserId()
{
    return userId;
}

// Stock symbol return karega
string Order::getStockSymbol()
{
    return stockSymbol;
}

// BUY ya SELL return karega
string Order::getSide()
{
    return side;
}

// Current remaining quantity return karega
int Order::getQuantity()
{
    return quantity;
}

// Matching ke baad remaining quantity update karega
void Order::setQuantity(int quantity)
{
    this->quantity = quantity;
}

// Order price return karega
double Order::getPrice()
{
    return price;
}

// Order ka timestamp return karega
string Order::getTimestamp()
{
    return timestamp;
}

// MARKET ya LIMIT order type return karega
string Order::getOrderType()
{
    return orderType;
}