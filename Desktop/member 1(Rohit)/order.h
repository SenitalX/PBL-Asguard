#ifndef ORDER_H
#define ORDER_H

#include <string>
using namespace std;

// Order class ek BUY ya SELL order ki complete information store karti hai
class Order
{
private:
    int orderId;
    int userId;
    string stockSymbol;
    string side;          // BUY / SELL
    int quantity;
    double price;
    string timestamp;
    string orderType;     // MARKET / LIMIT

public:
    // Constructor
    Order(int orderId,
          int userId,
          string stockSymbol,
          string side,
          int quantity,
          double price,
          string timestamp,
          string orderType);

    // Order details access karne ke liye getters
    int getOrderId();
    int getUserId();
    string getStockSymbol();
    string getSide();
    int getQuantity();
    double getPrice();
    string getTimestamp();
    string getOrderType();

    // Matching ke baad remaining quantity update karne ke liye
    void setQuantity(int quantity);
};

#endif