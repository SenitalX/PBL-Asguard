#ifndef TRADE_H
#define TRADE_H

#include <string>

class Trade {

private:

    int tradeId;
    int buyOrderId;
    int sellOrderId;

    std::string symbol;

    int quantity;
    double price;

public:

    Trade(
        int tradeId,
        int buyOrderId,
        int sellOrderId,
        const std::string& symbol,
        int quantity,
        double price
    );

    int getTradeId() const;
    int getBuyOrderId() const;
    int getSellOrderId() const;

    std::string getSymbol() const;

    int getQuantity() const;
    double getPrice() const;
};

#endif