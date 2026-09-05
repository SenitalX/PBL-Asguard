import { useState } from "react";
import type { OrderSide, OrderType } from "../types";
import { placeOrder } from "../services/api";

interface Props {
  symbol: string;
  defaultPrice: number;
  onSuccess?: () => void;
}

export default function OrderForm({ symbol, defaultPrice, onSuccess }: Props) {
  const [side, setSide] = useState<OrderSide>("BUY");
  const [quantity, setQuantity] = useState(10);
  const [price, setPrice] = useState(defaultPrice);
  const [orderType, setOrderType] = useState<OrderType>("LIMIT");
  const [message, setMessage] = useState("");
  const [error, setError] = useState("");
  const [loading, setLoading] = useState(false);

  async function submitOrder(event: React.FormEvent) {
    event.preventDefault();
    setMessage("");
    setError("");
    setLoading(true);

    try {
      const result = await placeOrder({
        userId: 1,
        symbol,
        side,
        quantity,
        price: orderType === "MARKET" ? defaultPrice : price,
        orderType
      });

      setMessage(`Order #${result.orderId} ${result.status?.toLowerCase()}.`);
      onSuccess?.();
    } catch (err) {
      setError(err instanceof Error ? err.message : "Order failed.");
    } finally {
      setLoading(false);
    }
  }

  const total = quantity * (orderType === "MARKET" ? defaultPrice : price);

  return (
    <form className="order-form" onSubmit={submitOrder}>
      <div className="side-toggle">
        <button type="button" className={side === "BUY" ? "active buy" : ""} onClick={() => setSide("BUY")}>BUY</button>
        <button type="button" className={side === "SELL" ? "active sell" : ""} onClick={() => setSide("SELL")}>SELL</button>
      </div>

      <label>
        Quantity
        <input type="number" min="1" value={quantity} onChange={(e) => setQuantity(Number(e.target.value))} />
      </label>

      <label>
        Order Type
        <select value={orderType} onChange={(e) => setOrderType(e.target.value as OrderType)}>
          <option value="LIMIT">LIMIT</option>
          <option value="MARKET">MARKET</option>
        </select>
      </label>

      <label>
        Price
        <input
          type="number"
          min="0.01"
          step="0.01"
          value={price}
          disabled={orderType === "MARKET"}
          onChange={(e) => setPrice(Number(e.target.value))}
        />
      </label>

      <div className="order-total">
        <span>Estimated value</span>
        <strong>₹{total.toLocaleString("en-IN")}</strong>
      </div>

      <button className={`primary-action ${side === "SELL" ? "sell-action" : ""}`} disabled={loading}>
        {loading ? "Processing..." : `Place ${side} Order`}
      </button>

      {message && <div className="success-message">✓ {message}</div>}
      {error && <div className="error-message">! {error}</div>}
    </form>
  );
}