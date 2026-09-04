#include "../include/Trade.h"

Trade::Trade(
    int tradeId,
    int buyOrderId,
    int sellOrderId,
    const std::string& symbol,
    int quantity,
    double price
)
    : tradeId(tradeId),
      buyOrderId(buyOrderId),
      sellOrderId(sellOrderId),
      symbol(symbol),
      quantity(quantity),
      price(price)
{
}

int Trade::getTradeId() const {
    return tradeId;
}

int Trade::getBuyOrderId() const {
    return buyOrderId;
}

int Trade::getSellOrderId() const {
    return sellOrderId;
}

std::string Trade::getSymbol() const {
    return symbol;
}

int Trade::getQuantity() const {
    return quantity;
}

double Trade::getPrice() const {
    return price;
}