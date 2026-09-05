import type { Portfolio, Stock } from "../types";

export const stocks: Stock[] = [
  { symbol: "RELIANCE", name: "Reliance Industries", price: 1450, change: 2.1, volume: 125000 },
  { symbol: "TCS", name: "Tata Consultancy Services", price: 3200, change: -0.8, volume: 85000 },
  { symbol: "INFY", name: "Infosys", price: 1800, change: 1.4, volume: 95000 },
  { symbol: "HDFC", name: "HDFC Bank", price: 1650, change: 0.6, volume: 75000 },
  { symbol: "ITC", name: "ITC Limited", price: 450, change: -0.2, volume: 150000 }
];

export const initialPortfolio: Portfolio = {
  balance: 100000,
  portfolioValue: 0,
  profitLoss: 0,
  holdings: []
};