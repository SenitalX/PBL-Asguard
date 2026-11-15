const API_BASE = '';

const API = {
    async placeOrder(order) {
        if (!API_BASE) {
            return mockPlaceOrder(order);
        }
        const res = await fetch(API_BASE + '/api/orders', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(order)
        });
        return res.json();
    },

    async getOrders() {
        if (!API_BASE) return mockGetOrders();
        const res = await fetch(API_BASE + '/api/orders');
        return res.json();
    },

    async getTrades() {
        if (!API_BASE) return mockGetTrades();
        const res = await fetch(API_BASE + '/api/trades');
        return res.json();
    },

    async getPortfolio() {
        if (!API_BASE) return mockGetPortfolio();
        const res = await fetch(API_BASE + '/api/portfolio');
        return res.json();
    }
};

function mockPlaceOrder(order) {
    const orders = JSON.parse(localStorage.getItem('hft_orders') || '[]');
    const newOrder = {
        id: 'ORD-' + Math.floor(Math.random() * 9000 + 1000),
        stock: order.stock,
        side: order.side,
        type: order.type,
        qty: order.qty,
        price: order.price,
        time: new Date().toLocaleTimeString(),
        status: 'FILLED'
    };
    orders.push(newOrder);
    localStorage.setItem('hft_orders', JSON.stringify(orders));
    return new Promise(resolve => setTimeout(() => resolve(newOrder), 400));
}

function mockGetOrders() {
    const orders = JSON.parse(localStorage.getItem('hft_orders') || '[]');
    return Promise.resolve(orders);
}

function mockGetTrades() {
    const orders = JSON.parse(localStorage.getItem('hft_orders') || '[]');
    const trades = orders.filter(o => o.status === 'FILLED').map(o => ({
        id: 'TRD-' + o.id.split('-')[1],
        stock: o.stock,
        side: o.side,
        qty: o.qty,
        price: o.price,
        time: o.time,
        status: o.status
    }));
    return Promise.resolve(trades);
}

function mockGetPortfolio() {
    const orders = JSON.parse(localStorage.getItem('hft_orders') || '[]');
    const holdings = {};
    let cash = 100000;

    orders.forEach(o => {
        if (o.side === 'BUY') {
            cash -= o.qty * o.price;
            if (!holdings[o.stock]) holdings[o.stock] = { qty: 0, invested: 0 };
            holdings[o.stock].qty += o.qty;
            holdings[o.stock].invested += o.qty * o.price;
        } else {
            cash += o.qty * o.price;
            if (holdings[o.stock]) {
                holdings[o.stock].qty -= o.qty;
                holdings[o.stock].invested -= o.qty * o.price;
                if (holdings[o.stock].qty <= 0) delete holdings[o.stock];
            }
        }
    });

    let invested = 0;
    Object.keys(holdings).forEach(k => { invested += holdings[k].invested; });

    return Promise.resolve({ cash, invested, holdings });
}