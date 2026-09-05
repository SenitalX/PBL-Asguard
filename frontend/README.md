# TradeSim — Phase 1 Frontend

A ready-to-run React + TypeScript frontend for the Stock Market Simulator college PBL.

## Phase 1 demo flow

Home → Login → Dashboard → Market → Stock Details → BUY/SELL → Order response → Portfolio → Orders/Trades

## Tech

- React
- TypeScript
- Vite
- React Router
- CSS

## Run

```bash
npm install
npm run dev
```

Open the local URL printed by Vite.

## Demo mode

The project runs immediately without a backend. It uses simulated market data and stores demo orders, trades and portfolio data in browser localStorage.

To reset the demo:
- Open browser DevTools
- Application/Storage → Local Storage
- Delete keys beginning with `tradesim_`

## Connect Member 2's backend

Create a `.env` file:

```env
VITE_API_BASE_URL=http://localhost:8080
```

Then restart Vite.

The frontend expects:

- `POST /api/orders`
- `GET /api/orders?userId=1`
- `GET /api/trades?userId=1`
- `GET /api/market`
- `GET /api/portfolio?userId=1`

The request/response contract should be finalized with the backend member before integration.

## Phase 1 mentor demo

1. Open Dashboard.
2. Go to Market.
3. Open RELIANCE.
4. Enter quantity 10 and price 1450.
5. Click BUY.
6. Show the filled response.
7. Return to Dashboard and show balance/holding update.
8. Open Orders and Trades to show the recorded transaction.

The mock engine marks valid demo orders as FILLED so the complete frontend flow can be demonstrated before the C++/backend integration is available.
