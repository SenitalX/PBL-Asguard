#ifndef MATCHING_ENGINE_H
#define MATCHING_ENGINE_H

#include "OrderManager.h"
#include "Trade.h"

#include <string>
#include <vector>

class MatchingEngine {
private:
    OrderManager& orderManager;
    int nextTradeId;

public:
    explicit MatchingEngine(OrderManager& manager);

    void matchOrder(
        int incomingOrderId,
        std::vector<Trade>& trades
    );
};

#endif