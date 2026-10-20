# Member 3 — Clean C++ + DSA Portfolio Demo

## Compile on Windows PowerShell
```powershell
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o portfolio_demo.exe
.\portfolio_demo.exe
```

## DSA used
- `unordered_map<int, User>`: average O(1) user lookup.
- `map<string, Stock>`: stock lookup in O(log S), sorted symbols.
- `map<string, Holding>`: holding lookup in O(log H).
- `vector<ExecutedTrade>`: executed trade history, amortized O(1) append.
- OOP classes: `UserManager`, `Market`, `Portfolio`.

## Demo
- Start cash Rs 100000.
- BUY 10 RELIANCE @ Rs 1450 -> cash Rs 85500.
- SELL 5 RELIANCE @ Rs 1600 -> cash Rs 93500, 5 shares remain.
- Realized P/L Rs 750.
- Selling 100 shares is rejected.

This is a standalone educational module with simulated prices. It is not yet connected to the shared website/backend. The CSV saves holdings and realized P/L; user balance persistence and production database integration are not included.
