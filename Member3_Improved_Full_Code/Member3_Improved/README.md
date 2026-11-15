# Member 3: User + Market + Portfolio module

## Files
- `Member3Module.h`: public data structures and class interfaces.
- `Member3Module.cpp`: implementation.
- `member3_demo.cpp`: standalone demo entry point.

## Build and run (C++17)
```bash
g++ -std=c++17 -Wall -Wextra -pedantic Member3Module.cpp member3_demo.cpp -o member3_demo
./member3_demo
```

## Features
- Multiple users, each with a separate portfolio.
- User and portfolio lookup by ID.
- Market stock lookup and display.
- BUY/SELL executed-trade application with cash/share validation.
- Average buy price, realized P/L, unrealized P/L.
- CSV save and load for user cash, holdings, realized P/L and trade history.

## Important integration note
This module does NOT directly call your team's `TradeEngine` yet because its exact `Trade` structure and getter names must match the backend. After a backend match is produced, adapt it into two `ExecutedTrade` records:
- buyer record: `side = "BUY"`, buyer user ID
- seller record: `side = "SELL"`, seller user ID

Then call `UserManager::applyExecutedTrade()` for each side. Do this only after the engine has validated/reserved funds and shares. For a robust production system, both portfolio updates should be atomic (both succeed or neither is committed).

`member3_demo.cpp` is a standalone demo. Do not compile it together with the final application's other `main()` function.
