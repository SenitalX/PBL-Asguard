#include "order.h"
//Pehla Order: Ye function Order class ka hai.
// secod order - Function ka naam Order hai.
Order::Order(int orderId,
             int userId,
             string stockSymbol,
             string side,
             int quantity,
             double price,
             string timestamp,
             string orderType)
{
    //// this-> = current object ka variable, right side = parameter
    this->orderId = orderId;// // object ka orderId = parameter ki value
    this->userId = userId;
    this->stockSymbol = stockSymbol;
    this->side = side;
    this->quantity = quantity;
    this->price = price;
    this->timestamp = timestamp;
    this->orderType = orderType;
}

int Order::getOrderId()
{
    return orderId; //object ka order id return karega(value nikal ke dega)
}

int Order::getUserId()
{
    return userId;
}

string Order::getStockSymbol()
{
    return stockSymbol;
}

string Order::getSide()
{
    return side;
}

int Order::getQuantity()
{
    return quantity;
}

double Order::getPrice()
{
    return price;
}

string Order::getTimestamp()
{
    return timestamp;
}

string Order::getOrderType()
{
    return orderType;
}