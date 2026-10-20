
#include <iostream>
#include <algorithm>
#include "advanced_matching_engine.h"

using namespace std;

bool AdvancedMatchingEngine::canMatch(
    Order& buyOrder,
    Order& sellOrder)
{
    if (buyOrder.getStockSymbol() != sellOrder.getStockSymbol())
        return false;

    if (buyOrder.getUserId() == sellOrder.getUserId())
        return false;

    if (buyOrder.getSide() != "BUY" ||
        sellOrder.getSide() != "SELL")
        return false;

    if (buyOrder.getOrderType() != "LIMIT" ||
        sellOrder.getOrderType() != "LIMIT")
        return false;

    if (buyOrder.getPrice() <= 0 ||
        sellOrder.getPrice() <= 0 ||
        buyOrder.getQuantity() <= 0 ||
        sellOrder.getQuantity() <= 0)
        return false;

    if (buyOrder.getPrice() < sellOrder.getPrice())
        return false;

    return true;
}

void AdvancedMatchingEngine::matchOrders(
    vector<Order>& buyOrders,
    vector<Order>& sellOrders)
{
    // BUY: highest price first
    sort(buyOrders.begin(), buyOrders.end(),
        [](Order& a, Order& b)
        {
            if (a.getPrice() != b.getPrice())
                return a.getPrice() > b.getPrice();

            return a.getTimestamp() < b.getTimestamp();
        });

    // SELL: lowest price first
    sort(sellOrders.begin(), sellOrders.end(),
        [](Order& a, Order& b)
        {
            if (a.getPrice() != b.getPrice())
                return a.getPrice() < b.getPrice();

            return a.getTimestamp() < b.getTimestamp();
        });

    cout << "\n===== ADVANCED MATCHING STARTED =====\n";

    for (Order& buyOrder : buyOrders)
    {
        for (Order& sellOrder : sellOrders)
        {
            if (buyOrder.getQuantity() <= 0)
                break;

            if (sellOrder.getQuantity() <= 0)
                continue;

            if (!canMatch(buyOrder, sellOrder))
                continue;

            int executedQuantity = min(
                buyOrder.getQuantity(),
                sellOrder.getQuantity()
            );

            cout << "\nTRADE EXECUTED\n";
            cout << "Stock: " << buyOrder.getStockSymbol() << '\n';
            cout << "Buy Order ID: " << buyOrder.getOrderId() << '\n';
            cout << "Sell Order ID: " << sellOrder.getOrderId() << '\n';
            cout << "Quantity: " << executedQuantity << '\n';
            cout << "Price: " << sellOrder.getPrice() << '\n';

            buyOrder.setQuantity(
                buyOrder.getQuantity() - executedQuantity
            );

            sellOrder.setQuantity(
                sellOrder.getQuantity() - executedQuantity
            );
        }
    }

    cout << "\n===== ADVANCED MATCHING COMPLETED =====\n";
}
