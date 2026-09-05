import { NavLink } from "react-router-dom";

export default function Navbar() {
  return (
    <header className="navbar">
      <div className="nav-inner">
        <NavLink to="/" className="brand">
          <span className="brand-mark">T</span>
          <span>TradeSim</span>
        </NavLink>

        <nav className="nav-links">
          <NavLink to="/dashboard">Dashboard</NavLink>
          <NavLink to="/market">Market</NavLink>
          <NavLink to="/orders">Orders</NavLink>
          <NavLink to="/trades">Trades</NavLink>
        </nav>

        <NavLink to="/login" className="nav-login">Login</NavLink>
      </div>
    </header>
  );
}