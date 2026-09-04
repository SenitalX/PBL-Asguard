#include <iostream>
#include "order.h"
#include "orderbook.h"

using namespace std;

int main()
{
    // Buy orders
    Order buyOrder1(
        101,
        1,
        "RELIANCE",
        "BUY",
        10,
        1450.0,
        "10:30:15",
        "LIMIT"
    );
    Order buyOrder2(
        102,
        2,
        "TCS",
        "BUY",
        5,
        3200.0,
        "10:35:20",
        "LIMIT"
    );
    // Sell order
    Order sellOrder1(
        103,
        3,
        "RELIANCE",
        "SELL",
        8,
        1450.0,
        "10:40:10",
        "LIMIT"
    );
    // Create OrderBook object
    OrderBook orderBook;
    // Add orders
    orderBook.addBuyOrder(buyOrder1);
    orderBook.addBuyOrder(buyOrder2);
    orderBook.addSellOrder(sellOrder1);

    // Get orders
    vector<Order> buyOrders = orderBook.getBuyOrders();
    vector<Order> sellOrders = orderBook.getSellOrders();

    // Print Buy Orders
    cout << "BUY ORDERS:" << endl;

    for (int i = 0; i < buyOrders.size(); i++)
    {
        cout << buyOrders[i].getStockSymbol()
             << " | "
             << buyOrders[i].getSide()
             << " | Quantity: "
             << buyOrders[i].getQuantity()
             << " | Price: "
             << buyOrders[i].getPrice()
             << endl;
    }
    // Print Sell Orders
    cout << "\nSELL ORDERS:" << endl;

    for (int i = 0; i < sellOrders.size(); i++)
    {
        cout << sellOrders[i].getStockSymbol()
             << " | "
             << sellOrders[i].getSide()
             << " | Quantity: "
             << sellOrders[i].getQuantity()
             << " | Price: "
             << sellOrders[i].getPrice()
             << endl;
    }
    return 0;
}