const fs = require('fs')

let orders = []

for (let i = 0; i < 30000; i++) {
  let order = {
    id: i,
    total: i+1
  }
  orders.push(order)
}

fs.writeFileSync('orders.json', JSON.stringify(orders))
