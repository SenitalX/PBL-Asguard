import type { Order, Portfolio, Stock } from "../types";
import { initialPortfolio, stocks } from "../data/mockData";

const API_BASE_URL = import.meta.env.VITE_API_BASE_URL || "";
const USE_MOCK_API = !API_BASE_URL;

const delay = (ms: number) => new Promise((resolve) => setTimeout(resolve, ms));

export async function getMarket(): Promise<Stock[]> {
  if (USE_MOCK_API) {
    await delay(350);
    return stocks;
  }

  const response = await fetch(`${API_BASE_URL}/api/market`);
  if (!response.ok) throw new Error("Unable to load market data.");
  return response.json();
}

export async function getPortfolio(userId = 1): Promise<Portfolio> {
  if (USE_MOCK_API) {
    await delay(250);
    const stored = localStorage.getItem("tradesim_portfolio");
    return stored ? JSON.parse(stored) : initialPortfolio;
  }

  const response = await fetch(`${API_BASE_URL}/api/portfolio?userId=${userId}`);
  if (!response.ok) throw new Error("Unable to load portfolio.");
  return response.json();
}

export async function getOrders(userId = 1): Promise<Order[]> {
  if (USE_MOCK_API) {
    await delay(250);
    const stored = localStorage.getItem("tradesim_orders");
    return stored ? JSON.parse(stored) : [];
  }

  const response = await fetch(`${API_BASE_URL}/api/orders?userId=${userId}`);
  if (!response.ok) throw new Error("Unable to load orders.");
  return response.json();
}

export async function getTrades(userId = 1): Promise<Order[]> {
  if (USE_MOCK_API) {
    await delay(250);
    const stored = localStorage.getItem("tradesim_trades");
    return stored ? JSON.parse(stored) : [];
  }

  const response = await fetch(`${API_BASE_URL}/api/trades?userId=${userId}`);
  if (!response.ok) throw new Error("Unable to load trades.");
  return response.json();
}

export async function placeOrder(order: Order): Promise<Order> {
  if (!USE_MOCK_API) {
    const response = await fetch(`${API_BASE_URL}/api/orders`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(order)
    });
    if (!response.ok) {
      const message = await response.text();
      throw new Error(message || "Order was rejected by the server.");
    }
    return response.json();
  }

  await delay(700);

  const stock = stocks.find((item) => item.symbol === order.symbol);
  if (!stock) throw new Error("Invalid stock.");
  if (order.quantity <= 0) throw new Error("Quantity must be greater than zero.");
  if (order.price <= 0) throw new Error("Price must be greater than zero.");

  const newOrder: Order = {
    ...order,
    orderId: Date.now(),
    status: "FILLED",
    createdAt: new Date().toISOString()
  };

  const existingOrders: Order[] = JSON.parse(localStorage.getItem("tradesim_orders") || "[]");
  localStorage.setItem("tradesim_orders", JSON.stringify([newOrder, ...existingOrders]));

  const existingTrades: Order[] = JSON.parse(localStorage.getItem("tradesim_trades") || "[]");
  localStorage.setItem("tradesim_trades", JSON.stringify([newOrder, ...existingTrades]));

  const current: Portfolio = JSON.parse(
    localStorage.getItem("tradesim_portfolio") || JSON.stringify(initialPortfolio)
  );

  const tradeValue = order.quantity * order.price;

  if (order.side === "BUY") {
    if (tradeValue > current.balance) throw new Error("Insufficient balance.");
    current.balance -= tradeValue;

    const holding = current.holdings.find((h) => h.symbol === order.symbol);
    if (holding) {
      const oldValue = holding.quantity * holding.averagePrice;
      holding.quantity += order.quantity;
      holding.averagePrice = (oldValue + tradeValue) / holding.quantity;
    } else {
      current.holdings.push({
        symbol: order.symbol,
        quantity: order.quantity,
        averagePrice: order.price
      });
    }
  } else {
    const holding = current.holdings.find((h) => h.symbol === order.symbol);
    if (!holding || holding.quantity < order.quantity) {
      throw new Error("Insufficient holdings to sell.");
    }

    holding.quantity -= order.quantity;
    current.balance += tradeValue;

    if (holding.quantity === 0) {
      current.holdings = current.holdings.filter((h) => h.symbol !== order.symbol);
    }
  }

  current.portfolioValue = current.holdings.reduce((sum, holding) => {
    const currentStock = stocks.find((s) => s.symbol === holding.symbol);
    return sum + holding.quantity * (currentStock?.price || holding.averagePrice);
  }, 0);

  current.profitLoss = current.holdings.reduce((sum, holding) => {
    const currentStock = stocks.find((s) => s.symbol === holding.symbol);
    return sum + holding.quantity * ((currentStock?.price || holding.averagePrice) - holding.averagePrice);
  }, 0);

  localStorage.setItem("tradesim_portfolio", JSON.stringify(current));

  return newOrder;
}

export function resetDemoData() {
  localStorage.removeItem("tradesim_orders");
  localStorage.removeItem("tradesim_trades");
  localStorage.removeItem("tradesim_portfolio");
}