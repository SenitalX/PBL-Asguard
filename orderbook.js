async function loadOrderBook() {
    const orders = await API.getOrders();
    const buys = orders.filter(o => o.side === 'BUY');
    const sells = orders.filter(o => o.side === 'SELL');

    const buyTable = document.getElementById('buyTable');
    if (buys.length === 0) {
        buyTable.innerHTML = '<tr><td colspan="4" class="empty">No buy orders.</td></tr>';
    } else {
        buyTable.innerHTML = buys.map(o =>
            '<tr><td>' + o.id + '</td><td>' + o.stock + '</td><td class="buy">₹' + o.price + '</td><td>' + o.qty + '</td></tr>'
        ).join('');
    }

    const sellTable = document.getElementById('sellTable');
    if (sells.length === 0) {
        sellTable.innerHTML = '<tr><td colspan="4" class="empty">No sell orders.</td></tr>';
    } else {
        sellTable.innerHTML = sells.map(o =>
            '<tr><td>' + o.id + '</td><td>' + o.stock + '</td><td class="sell">₹' + o.price + '</td><td>' + o.qty + '</td></tr>'
        ).join('');
    }
}

loadOrderBook();