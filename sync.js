const orders = require('./data/orders.json')

function syncTest(requestId) {
  const logMsg = `Execution time for sync request ${requestId}`
  console.time(logMsg)
  let total = 0
  for (let i = 0; i < orders.length; i++) {
    let internalTotal = 0
    for (let j = 0; j < orders.length; j++) {
      internalTotal += orders[i].total
    }
    total += orders[i].total
  }

  console.log("I'm done and the total is:", total)
  console.timeEnd(logMsg)
}

// syncTest()
module.exports = syncTest;
//
