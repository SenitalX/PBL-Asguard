let currentSide = 'BUY';

function setSide(side) {
    currentSide = side;
    const buyBtn = document.getElementById('buyBtn');
    const sellBtn = document.getElementById('sellBtn');
    buyBtn.className = side === 'BUY' ? 'active-buy' : '';
    sellBtn.className = side === 'SELL' ? 'active-sell' : '';
}

function resetForm() {
    document.getElementById('stockInput').value = 'RELIANCE';
    document.getElementById('typeInput').value = 'LIMIT';
    document.getElementById('qtyInput').value = '10';
    document.getElementById('priceInput').value = '1450';
    setSide('BUY');
    document.getElementById('message').style.display = 'none';
}

async function submitOrder() {
    const stock = document.getElementById('stockInput').value.trim().toUpperCase();
    const type = document.getElementById('typeInput').value;
    const qty = parseInt(document.getElementById('qtyInput').value);
    const price = parseFloat(document.getElementById('priceInput').value);
    const msg = document.getElementById('message');

    if (!stock) {
        showMessage('error', 'Please enter a stock symbol.');
        return;
    }
    if (!qty || qty <= 0) {
        showMessage('error', 'Quantity must be greater than zero.');
        return;
    }
    if (type === 'LIMIT' && (!price || price <= 0)) {
        showMessage('error', 'Price must be greater than zero for LIMIT orders.');
        return;
    }

    const btn = event.target;
    btn.disabled = true;
    btn.textContent = 'Processing...';

    try {
        const result = await API.placeOrder({ stock, side: currentSide, type, qty, price });
        showMessage('success', currentSide + ' order ' + result.id + ' placed: ' + qty + ' × ' + stock + ' @ ₹' + price + ' — Status: ' + result.status);
    } catch (err) {
        showMessage('error', 'Order failed. Please try again.');
    }

    btn.disabled = false;
    btn.textContent = 'Submit Order';
}

function showMessage(type, text) {
    const msg = document.getElementById('message');
    msg.className = 'message ' + type;
    msg.textContent = text;
}