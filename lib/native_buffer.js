const async = require('bindings')('async');
const fs = require('fs');
// const orders = require('../data/orders.json')

// const buffer = Buffer.from('[{"id":1, "total":100}]', 'utf-8');
const buffer = Buffer.from(fs.readFileSync(`${__dirname}/../data/orders.json`, 'utf-8'), 'utf-8');

function getRandomInt(min, max) {
  min = Math.ceil(min);
  max = Math.floor(max);
  return Math.floor(Math.random() * (max - min)) + min;
}

function nativeTest(requestId) {
  const booleans = [false, false, false, true]
  const breakIt = booleans[getRandomInt(0,3)]

  return new Promise((resolve, reject) => {
    const logMsg = `Execution time for async request ${requestId}`
    console.time(logMsg)
    async.DoIt(
      buffer,
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
