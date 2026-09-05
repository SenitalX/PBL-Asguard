import { useEffect, useState } from "react";
import Navbar from "../components/Navbar";
import { getOrders } from "../services/api";
import type { Order } from "../types";

export default function Orders() {
  const [orders, setOrders] = useState<Order[]>([]);
  useEffect(() => { getOrders().then(setOrders); }, []);

  return (
    <>
      <Navbar />
      <main className="page-shell page">
        <div className="page-heading"><div><span className="eyebrow">ORDER MANAGEMENT</span><h1>My Orders</h1><p className="muted">Every order submitted through the trading screen.</p></div></div>
        <div className="panel table-panel">
          <div className="table-head order-grid"><span>ID</span><span>Stock</span><span>Side</span><span>Qty</span><span>Price</span><span>Status</span></div>
          {orders.length === 0 ? <div className="empty">No orders yet. Place one from a stock details page.</div> :
            orders.map(o => <div className="data-row order-grid" key={o.orderId}><span>#{o.orderId}</span><strong>{o.symbol}</strong><span className={o.side === "BUY" ? "positive" : "negative"}>{o.side}</span><span>{o.quantity}</span><span>₹{o.price.toLocaleString("en-IN")}</span><span className="badge">{o.status}</span></div>)}
        </div>
      </main>
    </>
  );
}