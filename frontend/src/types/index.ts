export type OrderSide = "BUY" | "SELL";
export type OrderType = "MARKET" | "LIMIT";
export type OrderStatus = "NEW" | "OPEN" | "FILLED" | "REJECTED";

export interface Stock {
  symbol: string;
  name: string;
  price: number;
  change: number;
  volume: number;
}

export interface Order {
  orderId?: number;
  userId: number;
  symbol: string;
  side: OrderSide;
  quantity: number;
  price: number;
  orderType: OrderType;
  status?: OrderStatus;
  createdAt?: string;
}

export interface Holding {
  symbol: string;
  quantity: number;
  averagePrice: number;
}

export interface Portfolio {
  balance: number;
  portfolioValue: number;
  profitLoss: number;
  holdings: Holding[];
}