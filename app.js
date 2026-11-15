async function loadDashboard() {
    const [orders, trades, portfolio] = await Promise.all([
        API.getOrders(),
        API.getTrades(),
        API.getPortfolio()
    ]);

    document.getElementById('statTotal').textContent = orders.length;
    document.getElementById('statMatched').textContent = orders.filter(o => o.status === 'FILLED').length;
    document.getElementById('statPending').textContent = orders.filter(o => o.status === 'PENDING').length;
    document.getElementById('statTrades').textContent = trades.length;

    document.getElementById('cashValue').textContent = '₹' + portfolio.cash.toFixed(2);
    document.getElementById('investedValue').textContent = '₹' + portfolio.invested.toFixed(2);
    document.getElementById('totalValue').textContent = '₹' + (portfolio.cash + portfolio.invested).toFixed(2);

    const holdingsDiv = document.getElementById('holdingsList');
    const keys = Object.keys(portfolio.holdings);
    if (keys.length === 0) {
        holdingsDiv.innerHTML = '<p class="empty">No holdings yet.</p>';
    } else {
        holdingsDiv.innerHTML = keys.map(stock => {
            const h = portfolio.holdings[stock];
            return '<div class="holding-row"><span>' + stock + '</span><strong>' + h.qty + ' × ₹' + (h.invested / h.qty).toFixed(2) + '</strong></div>';
        }).join('');
    }

    const tradesBody = document.getElementById('recentTrades');
    if (trades.length === 0) {
        tradesBody.innerHTML = '<tr><td colspan="6" class="empty">No trades yet.</td></tr>';
    } else {
        tradesBody.innerHTML = trades.slice(-5).reverse().map(t => {
            const cls = t.side === 'BUY' ? 'buy' : 'sell';
            return '<tr><td>' + t.id + '</td><td>' + t.stock + '</td><td class="' + cls + '">' + t.side + '</td><td>' + t.qty + '</td><td>₹' + t.price + '</td><td>' + t.time + '</td></tr>';
        }).join('');
    }
}

if (document.getElementById('statTotal')) {
    loadDashboard();
}