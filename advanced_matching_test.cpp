
#include <iostream>
#include <vector>
#include "advanced_matching_engine.h"

using namespace std;

int main()
{
    AdvancedMatchingEngine engine;

    vector<Order> buyOrders;
    vector<Order> sellOrders;

    // Test 1: Normal matching
    buyOrders.emplace_back(
        1, 101, "AAPL", "BUY", 10, 150.0, "10:00:00", "LIMIT"
    );

    sellOrders.emplace_back(
        2, 202, "AAPL", "SELL", 5, 145.0, "10:01:00", "LIMIT"
    );

    cout << "\nTEST 1: Normal Matching\n";
    engine.matchOrders(buyOrders, sellOrders);

    cout << "\nRemaining BUY Quantity: "
         << buyOrders[0].getQuantity() << '\n';

    cout << "Remaining SELL Quantity: "
         << sellOrders[0].getQuantity() << '\n';

    // Test 2: Different stock symbols
    vector<Order> buy2;
    vector<Order> sell2;

    buy2.emplace_back(
        3, 101, "AAPL", "BUY", 10, 150.0, "10:02:00", "LIMIT"
    );

    sell2.emplace_back(
        4, 202, "GOOGL", "SELL", 10, 140.0, "10:03:00", "LIMIT"
    );

    cout << "\nTEST 2: Different Stocks\n";
    engine.matchOrders(buy2, sell2);

    cout << "BUY Remaining: "
         << buy2[0].getQuantity() << '\n';

    cout << "SELL Remaining: "
         << sell2[0].getQuantity() << '\n';

    // Test 3: Same user orders
    vector<Order> buy3;
    vector<Order> sell3;

    buy3.emplace_back(
        5, 101, "AAPL", "BUY", 10, 150.0, "10:04:00", "LIMIT"
    );

    sell3.emplace_back(
        6, 101, "AAPL", "SELL", 10, 145.0, "10:05:00", "LIMIT"
    );

    cout << "\nTEST 3: Same User Orders\n";
    engine.matchOrders(buy3, sell3);

    cout << "BUY Remaining: "
         << buy3[0].getQuantity() << '\n';

    cout << "SELL Remaining: "
         << sell3[0].getQuantity() << '\n';

    // Test 4: BUY price is lower than SELL price
    vector<Order> buy4;
    vector<Order> sell4;

    buy4.emplace_back(
        7, 101, "AAPL", "BUY", 10, 140.0, "10:06:00", "LIMIT"
    );

    sell4.emplace_back(
        8, 202, "AAPL", "SELL", 10, 145.0, "10:07:00", "LIMIT"
    );

    cout << "\nTEST 4: Price Mismatch\n";
    engine.matchOrders(buy4, sell4);

    cout << "BUY Remaining: "
         << buy4[0].getQuantity() << '\n';

    cout << "SELL Remaining: "
         << sell4[0].getQuantity() << '\n';

    return 0;
}
