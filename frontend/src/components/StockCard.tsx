import { Link } from "react-router-dom";
import type { Stock } from "../types";

export default function StockCard({ stock }: { stock: Stock }) {
  const positive = stock.change >= 0;

  return (
    <Link to={`/stock/${stock.symbol}`} className="stock-card">
      <div>
        <div className="stock-symbol">{stock.symbol}</div>
        <div className="muted">{stock.name}</div>
      </div>
      <div className="stock-price">₹{stock.price.toLocaleString("en-IN")}</div>
      <div className={positive ? "change positive" : "change negative"}>
        {positive ? "+" : ""}{stock.change}%
      </div>
      <div className="muted volume">{stock.volume.toLocaleString("en-IN")} vol.</div>
      <span className="arrow">→</span>
    </Link>
  );
}