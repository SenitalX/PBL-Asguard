import { useEffect, useState } from "react";
import Navbar from "../components/Navbar";
import StockCard from "../components/StockCard";
import { getMarket } from "../services/api";
import type { Stock } from "../types";

export default function Market() {
  const [stocks, setStocks] = useState<Stock[]>([]);
  const [query, setQuery] = useState("");

  useEffect(() => { getMarket().then(setStocks); }, []);

  const filtered = stocks.filter(s => `${s.symbol} ${s.name}`.toLowerCase().includes(query.toLowerCase()));

  return (
    <>
      <Navbar />
      <main className="page-shell page">
        <div className="page-heading">
          <div><span className="eyebrow">SIMULATED MARKET</span><h1>Market</h1><p className="muted">Browse the available stocks and open a trading ticket.</p></div>
          <input className="search" placeholder="Search stocks..." value={query} onChange={e => setQuery(e.target.value)} />
        </div>
        <div className="market-table">
          <div className="table-head"><span>Stock</span><span>Price</span><span>Change</span><span>Volume</span><span></span></div>
          {filtered.map(stock => (
            <StockCard key={stock.symbol} stock={stock} />
          ))}
        </div>
      </main>
    </>
  );
}