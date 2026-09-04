#include <iostream>
#include "order.h"
#include "orderbook.h"

using namespace std;

int main()
{
    cout << "========================================" << endl;
    cout << "     STOCK MARKET MATCHING ENGINE       " << endl;
    cout << "========================================" << endl;

    OrderBook orderBook;

    // BUY ORDERS

    // Same stock, higher price gets higher priority
    Order buyOrder1(
        101,
        1,
        "RELIANCE",
        "BUY",
        10,
        1500.0,
        "10:30:15",
        "LIMIT"
    );

    // Same price orders: earlier time gets priority
    Order buyOrder2(
        102,
        2,
        "RELIANCE",
        "BUY",
        5,
        1450.0,
        "10:20:10",
        "LIMIT"
    );

    Order buyOrder3(
        103,
        3,
        "RELIANCE",
        "BUY",
        8,
        1450.0,
        "10:35:20",
        "LIMIT"
    );

    // Different stock order
    Order buyOrder4(
        104,
        4,
        "TCS",
        "BUY",
        10,
        3200.0,
        "10:25:00",
        "LIMIT"
    );

    // SELL ORDERS

    // Lower price gets higher priority
    Order sellOrder1(
        201,
        5,
        "RELIANCE",
        "SELL",
        8,
        1450.0,
        "10:40:10",
        "LIMIT"
    );

    Order sellOrder2(
        202,
        6,
        "RELIANCE",
        "SELL",
        10,
        1500.0,
        "10:45:20",
        "LIMIT"
    );

    // Different stock, should not match RELIANCE
    Order sellOrder3(
        203,
        7,
        "TCS",
        "SELL",
        5,
        3200.0,
        "10:50:00",
        "LIMIT"
    );

    // Add BUY orders
    orderBook.addBuyOrder(buyOrder1);
    orderBook.addBuyOrder(buyOrder2);
    orderBook.addBuyOrder(buyOrder3);
    orderBook.addBuyOrder(buyOrder4);

    // Add SELL orders
    orderBook.addSellOrder(sellOrder1);
    orderBook.addSellOrder(sellOrder2);
    orderBook.addSellOrder(sellOrder3);

    cout << "\nBEFORE MATCHING:" << endl;

    // Initial Order Book
    orderBook.displayOrderBook();

    // Start Matching Engine
    orderBook.matchOrders();

    cout << "\nAFTER MATCHING:" << endl;

    // Display remaining orders
    orderBook.displayOrderBook();

    cout << "\n========================================" << endl;
    cout << "       MATCHING ENGINE DEMO ENDED       " << endl;
    cout << "========================================" << endl;

    return 0;
}