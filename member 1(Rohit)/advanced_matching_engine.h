
#ifndef ADVANCED_MATCHING_ENGINE_H
#define ADVANCED_MATCHING_ENGINE_H

#include <vector>
#include "order.h"

class AdvancedMatchingEngine
{
public:
    void matchOrders(
        std::vector<Order>& buyOrders,
        std::vector<Order>& sellOrders
    );

private:
    bool canMatch(
        Order& buyOrder,
        Order& sellOrder
    );
};

#endif
