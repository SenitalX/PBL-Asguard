import { Link } from "react-router-dom";
import Navbar from "../components/Navbar";

export default function Home() {
  return (
    <>
      <Navbar />
      <main className="hero page-shell">
        <section className="hero-copy">
          <span className="eyebrow">COLLEGE PBL · PHASE 1</span>
          <h1>Learn the market.<br /><em>Practice the trade.</em></h1>
          <p>A simulated stock market where you can place BUY/SELL orders and see the complete trading flow without real money.</p>
          <div className="hero-actions">
            <Link to="/dashboard" className="button primary">Open Dashboard</Link>
            <Link to="/market" className="button secondary">Explore Market</Link>
          </div>
          <div className="hero-points">
            <span>✓ Simulated prices</span>
            <span>✓ Paper trading</span>
            <span>✓ Portfolio tracking</span>
          </div>
        </section>

        <section className="hero-panel">
          <div className="panel-head">
            <span>Portfolio overview</span>
            <span className="status-dot">Demo</span>
          </div>
          <div className="hero-balance">₹1,00,000</div>
          <div className="muted">Available balance</div>
          <div className="mini-chart">
            <span></span><span></span><span></span><span></span><span></span><span></span><span></span>
          </div>
          <div className="hero-metrics">
            <div><small>Portfolio</small><strong>₹0</strong></div>
            <div><small>P/L</small><strong className="positive">₹0</strong></div>
          </div>
        </section>
      </main>
    </>
  );
}