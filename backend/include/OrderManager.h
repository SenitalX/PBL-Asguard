#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H

#include "Order.h"
#include <unordered_map>
#include <vector>

class OrderManager {

private:

    std::unordered_map<int, Order> orders;

public:

    bool addOrder(const Order& order);

    Order* getOrder(int orderId);

    std::vector<Order> getAllOrders();

    bool updateOrderStatus(
        int orderId,
        OrderStatus status
    );

    bool cancelOrder(int orderId);
};

#endif