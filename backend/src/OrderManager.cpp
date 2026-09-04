#include "../include/OrderManager.h"

bool OrderManager::addOrder(const Order& order) {

    int id = order.getOrderId();

    // Check if order already exists
    if (orders.find(id) != orders.end()) {
        return false;
    }

    orders.emplace(id, order);

    return true;
}

Order* OrderManager::getOrder(int orderId) {

    auto it = orders.find(orderId);

    if (it == orders.end()) {
        return nullptr;
    }

    return &(it->second);
}

std::vector<Order> OrderManager::getAllOrders() {

    std::vector<Order> result;

    for (auto& pair : orders) {
        result.push_back(pair.second);
    }

    return result;
}

bool OrderManager::updateOrderStatus(
    int orderId,
    OrderStatus status
) {

    Order* order = getOrder(orderId);

    if (order == nullptr) {
        return false;
    }

    order->setStatus(status);

    return true;
}

bool OrderManager::cancelOrder(int orderId) {

    Order* order = getOrder(orderId);

    if (order == nullptr) {
        return false;
    }

    // Cannot cancel an already filled order
    if (order->getStatus() == OrderStatus::FILLED) {
        return false;
    }

    order->setStatus(OrderStatus::CANCELLED);

    return true;
}