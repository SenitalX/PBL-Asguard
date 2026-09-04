//Order ke andar kya-kya hoga?"

#ifndef ORDER_H  // "if not defined"
#define ORDER_H

#include <string>
using namespace std;

class Order
{
private:
    int orderId;
    int userId;
    string stockSymbol;
    string side;        // BUY / SELL
    int quantity;
    double price;
    string timestamp;
    string orderType;   // MARKET / LIMIT

public:
 //Constructor
    Order(int orderId,
          int userId,
          string stockSymbol,
          string side,
          int quantity,
          double price,
          string timestamp,
          string orderType);

    int getOrderId();
    int getUserId();
    string getStockSymbol();
    string getSide();
    int getQuantity();
    double getPrice();
    string getTimestamp();
    string getOrderType();
};

#endif