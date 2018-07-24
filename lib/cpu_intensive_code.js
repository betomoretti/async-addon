const {
  Worker, isMainThread, parentPort, workerData, threadId
} = require('worker_threads');

if (isMainThread) return;
  
const logMsg = `Execution time for sync request ${threadId}`
console.time(logMsg)
let total = 0
for (let i = 0; i < workerData.length; i++) {
  let internalTotal = 0
  for (let j = 0; j < workerData.length; j++) {
    internalTotal += workerData[i].total
  }
  total += workerData[i].total
}
console.log("I'm done and the total is:", total)

console.timeEnd(logMsg)