#include <iostream>
#include <algorithm>
#include "orderbook.h"

using namespace std;

// BUY order ko Order Book mein add karega
void OrderBook::addBuyOrder(Order order)
{
    buyOrders.push_back(order);
}

// SELL order ko Order Book mein add karega
void OrderBook::addSellOrder(Order order)
{
    sellOrders.push_back(order);
}

// Saare BUY orders return karega
vector<Order> OrderBook::getBuyOrders()
{
    return buyOrders;
}

// Saare SELL orders return karega
vector<Order> OrderBook::getSellOrders()
{
    return sellOrders;
}

// BUY orders ke liye Price-Time Priority
// Higher price pehle, same price par earlier timestamp pehle
void OrderBook::sortBuyOrders()
{
    sort(buyOrders.begin(), buyOrders.end(),
         [](Order a, Order b)
         {
             if (a.getPrice() == b.getPrice())
             {
                 return a.getTimestamp() < b.getTimestamp();
             }

             return a.getPrice() > b.getPrice();
         });
}

// SELL orders ke liye Price-Time Priority
// Lower price pehle, same price par earlier timestamp pehle
void OrderBook::sortSellOrders()
{
    sort(sellOrders.begin(), sellOrders.end(),
         [](Order a, Order b)
         {
             if (a.getPrice() == b.getPrice())
             {
                 return a.getTimestamp() < b.getTimestamp();
             }

             return a.getPrice() < b.getPrice();
         });
}

// BUY aur SELL orders ko match karega
void OrderBook::matchOrders()
{
    // Matching se pehle Price-Time Priority apply
    sortBuyOrders();
    sortSellOrders();

    cout << "\n========== MATCHING STARTED ==========" << endl;

    // Har BUY order ko SELL orders ke saath check karenge
    for (size_t i = 0; i < buyOrders.size(); i++)
    {
        for (size_t j = 0; j < sellOrders.size(); j++)
        {
            // Match conditions
            if (buyOrders[i].getStockSymbol() ==
                    sellOrders[j].getStockSymbol()
                &&
                buyOrders[i].getPrice() >=
                    sellOrders[j].getPrice()
                &&
                buyOrders[i].getQuantity() > 0
                &&
                sellOrders[j].getQuantity() > 0)
            {
                // Minimum quantity hi trade hogi
                int tradeQuantity = min(
                    buyOrders[i].getQuantity(),
                    sellOrders[j].getQuantity()
                );

                // Trade execution price
                double tradePrice = sellOrders[j].getPrice();

                cout << "\nTRADE GENERATED!" << endl;
                cout << "Stock: "
                     << buyOrders[i].getStockSymbol()
                     << endl;

                cout << "Buy Order ID: "
                     << buyOrders[i].getOrderId()
                     << endl;

                cout << "Sell Order ID: "
                     << sellOrders[j].getOrderId()
                     << endl;

                cout << "Quantity Matched: "
                     << tradeQuantity
                     << endl;

                cout << "Trade Price: "
                     << tradePrice
                     << endl;

                // BUY order ki remaining quantity update
                buyOrders[i].setQuantity(
                    buyOrders[i].getQuantity() - tradeQuantity
                );

                // SELL order ki remaining quantity update
                sellOrders[j].setQuantity(
                    sellOrders[j].getQuantity() - tradeQuantity
                );
            }
        }
    }

    cout << "\n========== MATCHING COMPLETED ==========" << endl;
}

// Current Order Book display karega
void OrderBook::displayOrderBook()
{
    cout << "\n========== BUY ORDER BOOK ==========" << endl;

    for (size_t i = 0; i < buyOrders.size(); i++)
    {
        if (buyOrders[i].getQuantity() > 0)
        {
            cout << "Order ID: "
                 << buyOrders[i].getOrderId()
                 << " | Stock: "
                 << buyOrders[i].getStockSymbol()
                 << " | Quantity: "
                 << buyOrders[i].getQuantity()
                 << " | Price: "
                 << buyOrders[i].getPrice()
                 << " | Time: "
                 << buyOrders[i].getTimestamp()
                 << endl;
        }
    }

    cout << "\n========== SELL ORDER BOOK ==========" << endl;

    for (size_t i = 0; i < sellOrders.size(); i++)
    {
        if (sellOrders[i].getQuantity() > 0)
        {
            cout << "Order ID: "
                 << sellOrders[i].getOrderId()
                 << " | Stock: "
                 << sellOrders[i].getStockSymbol()
                 << " | Quantity: "
                 << sellOrders[i].getQuantity()
                 << " | Price: "
                 << sellOrders[i].getPrice()
                 << " | Time: "
                 << sellOrders[i].getTimestamp()
                 << endl;
        }
    }
}