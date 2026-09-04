#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <vector>
#include "order.h"

using namespace std;

// OrderBook BUY/SELL orders ko store, sort aur match karega
class OrderBook
{
private:
    vector<Order> buyOrders;      // BUY orders
    vector<Order> sellOrders;     // SELL orders

public:
    // Naye orders add karne ke liye
    void addBuyOrder(Order order);
    void addSellOrder(Order order);

    // Orders access karne ke liye
    vector<Order> getBuyOrders();
    vector<Order> getSellOrders();

    // Price-Time Priority ke according sorting
    void sortBuyOrders();
    void sortSellOrders();

    // BUY aur SELL orders ko match karega
    void matchOrders();

    // Matching tests ke liye remaining orders display karega
    void displayOrderBook();
};

#endif