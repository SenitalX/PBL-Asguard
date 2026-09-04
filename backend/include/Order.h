#ifndef ORDER_H
#define ORDER_H

#include <string>

enum class OrderSide {
    BUY,
    SELL
};

enum class OrderType {
    MARKET,
    LIMIT
};

enum class OrderStatus {
    NEW,
    OPEN,
    PARTIALLY_FILLED,
    FILLED,
    CANCELLED
};

class Order {

private:

    int orderId;
    int userId;

    std::string symbol;

    OrderSide side;
    OrderType type;
    OrderStatus status;

    int quantity;
    int filledQuantity;

    double price;

public:

    Order(
        int orderId,
        int userId,
        const std::string& symbol,
        OrderSide side,
        OrderType type,
        int quantity,
        double price
    );

    int getOrderId() const;
    int getUserId() const;

    std::string getSymbol() const;

    OrderSide getSide() const;
    OrderType getType() const;
    OrderStatus getStatus() const;

    int getQuantity() const;
    int getFilledQuantity() const;

    double getPrice() const;

    void setStatus(OrderStatus status);
    void setFilledQuantity(int quantity);
};
#endif