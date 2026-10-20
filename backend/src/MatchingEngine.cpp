#include "../include/MatchingEngine.h"

#include <algorithm>

MatchingEngine::MatchingEngine(OrderManager& manager)
    : orderManager(manager), nextTradeId(1)
{
}

void MatchingEngine::matchOrder(
    int incomingOrderId,
    std::vector<Trade>& trades
) {
    Order* incoming = orderManager.getOrder(incomingOrderId);

    if (incoming == nullptr ||
        incoming->getStatus() == OrderStatus::CANCELLED ||
        incoming->getStatus() == OrderStatus::FILLED) {
        return;
    }

    // Collect existing orders. getAllOrders() returns copies.
    std::vector<Order> candidates = orderManager.getAllOrders();

    candidates.erase(
        std::remove_if(
            candidates.begin(),
            candidates.end(),
            [&](const Order& candidate) {
                if (candidate.getOrderId() == incomingOrderId)
                    return true;

                if (candidate.getSymbol() != incoming->getSymbol())
                    return true;

                if (candidate.getUserId() == incoming->getUserId())
                    return true;

                if (candidate.getType() != OrderType::LIMIT)
                    return true;

                if (candidate.getStatus() != OrderStatus::OPEN &&
                    candidate.getStatus() != OrderStatus::PARTIALLY_FILLED)
                    return true;

                if (candidate.getSide() == incoming->getSide())
                    return true;

                // Market orders can match at any available limit price.
                if (incoming->getType() == OrderType::MARKET)
                    return false;

                // Both orders are limit orders.
                if (incoming->getSide() == OrderSide::BUY)
                    return candidate.getPrice() > incoming->getPrice();

                return candidate.getPrice() < incoming->getPrice();
            }
        ),
        candidates.end()
    );

    // Price priority, then order ID as a deterministic tie-breaker.
    // This assumes order IDs increase with arrival time.
    std::sort(
        candidates.begin(),
        candidates.end(),
        [&](const Order& a, const Order& b) {
            if (a.getPrice() != b.getPrice()) {
                if (incoming->getSide() == OrderSide::BUY)
                    return a.getPrice() < b.getPrice();

                return a.getPrice() > b.getPrice();
            }

            return a.getOrderId() < b.getOrderId();
        }
    );

    for (const Order& candidate : candidates) {
        incoming = orderManager.getOrder(incomingOrderId);

        if (incoming == nullptr)
            return;

        int remaining =
            incoming->getQuantity() - incoming->getFilledQuantity();

        if (remaining <= 0)
            break;

        Order* resting =
            orderManager.getOrder(candidate.getOrderId());

        if (resting == nullptr)
            continue;

        int restingRemaining =
            resting->getQuantity() - resting->getFilledQuantity();

        if (restingRemaining <= 0)
            continue;

        int executedQuantity =
            std::min(remaining, restingRemaining);

        // Execute at the resting limit order's price.
        double executionPrice = resting->getPrice();

        int buyOrderId =
            incoming->getSide() == OrderSide::BUY
                ? incoming->getOrderId()
                : resting->getOrderId();

        int sellOrderId =
            incoming->getSide() == OrderSide::SELL
                ? incoming->getOrderId()
                : resting->getOrderId();

        trades.emplace_back(
            nextTradeId++,
            buyOrderId,
            sellOrderId,
            incoming->getSymbol(),
            executedQuantity,
            executionPrice
        );

        incoming->setFilledQuantity(
            incoming->getFilledQuantity() + executedQuantity
        );

        resting->setFilledQuantity(
            resting->getFilledQuantity() + executedQuantity
        );

        incoming->setStatus(
            incoming->getFilledQuantity() == incoming->getQuantity()
                ? OrderStatus::FILLED
                : OrderStatus::PARTIALLY_FILLED
        );

        resting->setStatus(
            resting->getFilledQuantity() == resting->getQuantity()
                ? OrderStatus::FILLED
                : OrderStatus::PARTIALLY_FILLED
        );
    }
}