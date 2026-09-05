import { FormEvent } from "react";
import { Link, useNavigate } from "react-router-dom";
import Navbar from "../components/Navbar";

export default function Register() {
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
          <span className="eyebrow">START SIMULATING</span>
          <h1>Create account</h1>
          <p className="muted">Create a demo trading profile for the PBL.</p>
          <label>Name<input placeholder="Your name" required /></label>
          <label>Email<input type="email" placeholder="you@example.com" required /></label>
          <label>Password<input type="password" placeholder="••••••••" required /></label>
          <button className="primary-action">Create Account</button>
          <p className="auth-footer">Already registered? <Link to="/login">Login</Link></p>
        </form>
      </main>
    </>
  );
}