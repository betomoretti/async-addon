const async = require('bindings')('async')
const orders = require('./data/orders.json')

function asyncTest(requestId) {
  return new Promise((resolve, reject) => {
    const logMsg = `Execution time for async request ${requestId}`
    console.time(logMsg)
    async.DoIt(
      orders,
      requestId,
      (error, total, workerId) => {
        if (error) return reject(error)
        console.log("I'm done and the total is:", total)
        console.timeEnd(logMsg)
        return resolve(workerId)
      }
    )
  })
}

module.exports = asyncTest;
