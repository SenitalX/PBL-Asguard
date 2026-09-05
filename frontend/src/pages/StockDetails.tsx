import { useEffect, useMemo, useState } from "react";
import { Link, useParams } from "react-router-dom";
import Navbar from "../components/Navbar";
import OrderForm from "../components/OrderForm";
import { getMarket } from "../services/api";
import type { Stock } from "../types";

export default function StockDetails() {
  const { symbol } = useParams();
  const [stocks, setStocks] = useState<Stock[]>([]);

  useEffect(() => { getMarket().then(setStocks); }, []);

  const stock = useMemo(() => stocks.find(s => s.symbol === symbol), [stocks, symbol]);

  if (!stock) {
    return <><Navbar /><main className="page-shell page"><div className="empty">Loading stock...</div></main></>;
  }

  const points = [34, 41, 37, 49, 45, 58, 54, 68, 64, 77, 73, 88];

  return (
    <>
      <Navbar />
      <main className="page-shell page">
        <Link to="/market" className="back">← Back to Market</Link>
        <div className="stock-layout">
          <section>
            <div className="stock-header">
              <div><span className="eyebrow">STOCK DETAILS</span><h1>{stock.symbol}</h1><p className="muted">{stock.name}</p></div>
              <div className="detail-price"><strong>₹{stock.price.toLocaleString("en-IN")}</strong><span className={stock.change >= 0 ? "positive" : "negative"}>{stock.change >= 0 ? "+" : ""}{stock.change}% today</span></div>
            </div>

            <div className="chart-panel">
              <div className="chart-labels"><span>Simulated price movement</span><span>1D</span></div>
              <div className="chart">
                {points.map((height, i) => <span key={i} style={{ height: `${height}%` }} />)}
              </div>
            </div>

            <div className="quote-grid">
              <div><span>Open</span><strong>₹{Math.round(stock.price * .99).toLocaleString("en-IN")}</strong></div>
              <div><span>High</span><strong>₹{Math.round(stock.price * 1.02).toLocaleString("en-IN")}</strong></div>
              <div><span>Low</span><strong>₹{Math.round(stock.price * .98).toLocaleString("en-IN")}</strong></div>
              <div><span>Volume</span><strong>{stock.volume.toLocaleString("en-IN")}</strong></div>
            </div>
          </section>

          <aside className="panel order-panel">
            <h2>Place order</h2>
            <p className="muted">Orders are simulated in Phase 1.</p>
            <OrderForm symbol={stock.symbol} defaultPrice={stock.price} />
          </aside>
        </div>
      </main>
    </>
  );
}