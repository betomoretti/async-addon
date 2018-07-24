const {
  Worker, isMainThread, parentPort, workerData
} = require('worker_threads');
const orders = require('./data/orders.json')

function workerTest() {
  const opts = { workerData: orders }
  new Worker('./cpu_intensive_code.js', opts)
}

module.exports = workerTest;
