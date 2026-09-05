import { useEffect, useState } from "react";
import Navbar from "../components/Navbar";
import { getTrades } from "../services/api";
import type { Order } from "../types";

export default function Trades() {
  const [trades, setTrades] = useState<Order[]>([]);
  useEffect(() => { getTrades().then(setTrades); }, []);

  return (
    <>
      <Navbar />
      <main className="page-shell page">
        <div className="page-heading"><div><span className="eyebrow">EXECUTED TRADES</span><h1>Trade History</h1><p className="muted">Generated trades from your simulated matching flow.</p></div></div>
        <div className="panel table-panel">
          <div className="table-head order-grid"><span>Trade ID</span><span>Stock</span><span>Side</span><span>Qty</span><span>Price</span><span>Status</span></div>
          {trades.length === 0 ? <div className="empty">No trades yet. A filled order will appear here.</div> :
            trades.map(t => <div className="data-row order-grid" key={t.orderId}><span>#{t.orderId}</span><strong>{t.symbol}</strong><span className={t.side === "BUY" ? "positive" : "negative"}>{t.side}</span><span>{t.quantity}</span><span>₹{t.price.toLocaleString("en-IN")}</span><span className="badge">EXECUTED</span></div>)}
        </div>
      </main>
    </>
  );
}