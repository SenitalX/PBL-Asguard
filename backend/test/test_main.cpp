#include "../include/Order.h"
#include "../include/OrderManager.h"
#include "../include/TradeEngine.h"
#include "../include/Trade.h"

#include <iostream>
#include <vector>

void testOrder(
    TradeEngine& engine,
    Order& order,
    const std::string& testName
) {
    std::vector<Trade> trades;
    std::string message;

    bool result = engine.processOrder(
        order,
        trades,
        message
    );

    std::cout << testName << "\n";

    if (result) {
        std::cout << "Result: ACCEPTED\n";
    } else {
        std::cout << "Result: REJECTED\n";
    }

    std::cout << "Message: "
              << message
              << "\n\n";
}

int main() {

    std::cout << "========================================\n";
    std::cout << "   TRADE ENGINE VALIDATION TEST\n";
    std::cout << "========================================\n\n";

    OrderManager orderManager;

    TradeEngine tradeEngine(orderManager);


    // TEST 1: Valid Order
    Order validOrder(
        101,
        1,
        "RELIANCE",
        OrderSide::BUY,
        OrderType::LIMIT,
        10,
        1450.0
    );

    testOrder(
        tradeEngine,
        validOrder,
        "TEST 1: Valid Order"
    );


    // TEST 2: Quantity = 0
    Order zeroQuantity(
        102,
        1,
        "TCS",
        OrderSide::BUY,
        OrderType::LIMIT,
        0,
        3200.0
    );

    testOrder(
        tradeEngine,
        zeroQuantity,
        "TEST 2: Zero Quantity"
    );


    // TEST 3: Negative Quantity
    Order negativeQuantity(
        103,
        1,
        "INFY",
        OrderSide::BUY,
        OrderType::LIMIT,
        -5,
        1500.0
    );

    testOrder(
        tradeEngine,
        negativeQuantity,
        "TEST 3: Negative Quantity"
    );


    // TEST 4: Empty Symbol
    Order emptySymbol(
        104,
        1,
        "",
        OrderSide::BUY,
        OrderType::LIMIT,
        10,
        1500.0
    );

    testOrder(
        tradeEngine,
        emptySymbol,
        "TEST 4: Empty Symbol"
    );


    // TEST 5: Invalid Price
    Order invalidPrice(
        105,
        1,
        "HDFC",
        OrderSide::BUY,
        OrderType::LIMIT,
        10,
        0
    );

    testOrder(
        tradeEngine,
        invalidPrice,
        "TEST 5: Zero Price"
    );


    // TEST 6: Duplicate Order ID
    Order duplicateOrder(
        101,
        2,
        "RELIANCE",
        OrderSide::SELL,
        OrderType::LIMIT,
        5,
        1450.0
    );

    testOrder(
        tradeEngine,
        duplicateOrder,
        "TEST 6: Duplicate Order ID"
    );


    std::cout << "========================================\n";
    std::cout << "          TESTING COMPLETE\n";
    std::cout << "========================================\n";

    return 0;
}