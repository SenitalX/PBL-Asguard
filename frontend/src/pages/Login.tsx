import { FormEvent } from "react";
import { Link, useNavigate } from "react-router-dom";
import Navbar from "../components/Navbar";

export default function Login() {
  const navigate = useNavigate();

  function submit(e: FormEvent) {
    e.preventDefault();
    navigate("/dashboard");
  }

  return (
    <>
      <Navbar />
      <main className="auth-page">
        <form className="auth-card" onSubmit={submit}>
          <span className="eyebrow">WELCOME BACK</span>
          <h1>Sign in</h1>
          <p className="muted">Use the demo account to enter your simulator.</p>
          <label>Email<input type="email" defaultValue="student@college.edu" required /></label>
          <label>Password<input type="password" defaultValue="password" required /></label>
          <button className="primary-action">Login to TradeSim</button>
          <p className="auth-footer">New here? <Link to="/register">Create an account</Link></p>
        </form>
      </main>
    </>
  );
}