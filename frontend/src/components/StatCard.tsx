interface Props {
  label: string;
  value: string;
  helper?: string;
  tone?: "default" | "positive" | "negative";
}

export default function StatCard({ label, value, helper, tone = "default" }: Props) {
  return (
    <div className="stat-card">
      <span className="muted">{label}</span>
      <strong className={tone}>{value}</strong>
      {helper && <small>{helper}</small>}
    </div>
  );
}