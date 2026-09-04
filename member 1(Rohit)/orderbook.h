#ifndef ORDERBOOK_H
#define ORDERBOOK_H
#include <vector>
#include "order.h"

using namespace std;

class OrderBook
{
private:
    vector<Order> buyOrders; //multiple values store kar sakte hain.
    vector<Order> sellOrders; //Multiple SELL orders store

public:
    void addBuyOrder(Order order);//Ek Order receive karo aur BUY Order Book mein add karo.
    void addSellOrder(Order order);//Ek Order receive karo aur sellOrders vector mein add karo

    vector<Order> getBuyOrders();//Saare BUY orders return karega
    vector<Order> getSellOrders();//Saare SELL orders return karega
};

#endif

