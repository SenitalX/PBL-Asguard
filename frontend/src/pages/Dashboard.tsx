import { useEffect, useState } from "react";
import Navbar from "../components/Navbar";
import StatCard from "../components/StatCard";
import StockCard from "../components/StockCard";
import { getMarket, getOrders, getPortfolio } from "../services/api";
import type { Order, Portfolio, Stock } from "../types";

export default function Dashboard() {
  const [portfolio, setPortfolio] = useState<Portfolio | null>(null);
  const [orders, setOrders] = useState<Order[]>([]);
  const [market, setMarket] = useState<Stock[]>([]);

  async function load() {
    const [p, o, m] = await Promise.all([getPortfolio(), getOrders(), getMarket()]);
    setPortfolio(p); setOrders(o); setMarket(m);
  }

  useEffect(() => { load(); }, []);

  return (
    <>
      <Navbar />
      <main className="page-shell page">
        <div className="page-heading">
          <div><span className="eyebrow">TRADING DESK</span><h1>Dashboard</h1><p className="muted">Your simulated trading account at a glance.</p></div>
          <button className="button secondary" onClick={load}>Refresh</button>
        </div>

        <section className="stats-grid">
          <StatCard label="Available balance" value={`₹${(portfolio?.balance ?? 100000).toLocaleString("en-IN")}`} helper="Paper cash" />
          <StatCard label="Portfolio value" value={`₹${(portfolio?.portfolioValue ?? 0).toLocaleString("en-IN")}`} helper="Current holdings" />
          <StatCard label="Profit / Loss" value={`₹${(portfolio?.profitLoss ?? 0).toLocaleString("en-IN")}`} helper="Unrealised P/L" tone={(portfolio?.profitLoss ?? 0) >= 0 ? "positive" : "negative"} />
        </section>

        <section className="content-grid">
          <div className="panel">
            <div className="panel-title"><h2>Holdings</h2><span className="muted">{portfolio?.holdings.length ?? 0} positions</span></div>
            {(portfolio?.holdings.length ?? 0) === 0 ? <div className="empty">No holdings yet. Visit the market and place your first order.</div> :
              portfolio?.holdings.map(h => <div className="holding-row" key={h.symbol}><strong>{h.symbol}</strong><span>{h.quantity} shares</span><span>Avg ₹{h.averagePrice.toLocaleString("en-IN")}</span></div>)}
          </div>

          <div className="panel">
            <div className="panel-title"><h2>Recent orders</h2><span className="muted">{orders.length}</span></div>
            {orders.length === 0 ? <div className="empty">No orders yet.</div> :
              orders.slice(0, 5).map(o => <div className="order-row" key={o.orderId}><strong>{o.symbol}</strong><span className={o.side === "BUY" ? "positive" : "negative"}>{o.side}</span><span>{o.quantity}</span><span className="badge">{o.status}</span></div>)}
          </div>
        </section>

        <section>
          <div className="section-heading"><h2>Market snapshot</h2><a href="/market">View all →</a></div>
          <div className="stock-grid">{market.slice(0, 3).map(stock => <StockCard key={stock.symbol} stock={stock} />)}</div>
        </section>
      </main>
    </>
  );
}