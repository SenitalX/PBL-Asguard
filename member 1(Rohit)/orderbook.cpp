#include "orderbook.h"
//BUY order ko Buy Order Book mein add karna.
void OrderBook::addBuyOrder(Order order)
{
    buyOrders.push_back(order);
}
//SELL order ko SELL Order Book mein add karna.
void OrderBook::addSellOrder(Order order)
{
    sellOrders.push_back(order);
}
vector<Order> OrderBook::getBuyOrders()//saare BUY orders wapas deta hai.
{
    return buyOrders;//jo bhi BUY orders stored hain, woh wapas bhej do.
}
vector<Order> OrderBook::getSellOrders()// Saare SELL orderwapas deta hai
{
    return sellOrders;// Jobhi sell order stored hai ,usko wpais bejdo
}