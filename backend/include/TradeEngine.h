#ifndef TRADE_ENGINE_H
#define TRADE_ENGINE_H

#include "Order.h"
#include "Trade.h"
#include "OrderManager.h"

#include <string>
#include <vector>

class TradeEngine {

private:

    OrderManager& orderManager;

    int nextTradeId;

    bool validateOrder(
        const Order& order,
        std::string& errorMessage
    );

public:

    TradeEngine(OrderManager& manager);

    bool processOrder(
        Order& order,
        std::vector<Trade>& trades,
        std::string& message
    );
};

#endif