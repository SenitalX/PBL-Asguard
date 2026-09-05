import { Routes, Route } from "react-router-dom";
import Home from "./pages/Home";
import Login from "./pages/Login";
import Register from "./pages/Register";
import Dashboard from "./pages/Dashboard";
import Market from "./pages/Market";
import StockDetails from "./pages/StockDetails";
import Orders from "./pages/Orders";
import Trades from "./pages/Trades";

export default function App() {
  return (
    <Routes>
      <Route path="/" element={<Home />} />
      <Route path="/login" element={<Login />} />
      <Route path="/register" element={<Register />} />
      <Route path="/dashboard" element={<Dashboard />} />
      <Route path="/market" element={<Market />} />
      <Route path="/stock/:symbol" element={<StockDetails />} />
      <Route path="/orders" element={<Orders />} />
      <Route path="/trades" element={<Trades />} />
    </Routes>
  );
}