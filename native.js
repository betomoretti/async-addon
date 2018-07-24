const async = require('bindings')('async')
const orders = require('./data/orders.json')

function getRandomInt(min, max) {
  min = Math.ceil(min);
  max = Math.floor(max);
  return Math.floor(Math.random() * (max - min)) + min;
}

function nativeTest(requestId) {
  const booleans = [false, false, false, true]
  const breakIt = booleans[getRandomInt(1,5)]

  return new Promise((resolve, reject) => {
    const logMsg = `Execution time for async request ${requestId}`
    console.time(logMsg)
    async.DoIt(
      orders,
      requestId,
      breakIt,
      (error, total, workerId) => {
        if (error) return reject(error)
        console.log("I'm done and the total is:", total)
        console.timeEnd(logMsg)
        return resolve(workerId)
      }
    )
  })
}

module.exports = nativeTest;
