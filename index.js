// process.env.UV_THREADPOOL_SIZE = Math.ceil(Math.max(4, require('os').cpus().length * 1.5));

const syncTest = require('./sync.js')
const asyncTest = require('./async.js')
const express = require('express')
const app = express()
let syncCounts = 0
let asyncCounts = 0

app.get('/sync', (req, res) => {
  syncCounts += 1
  syncTest(syncCounts)
  res.status(200)
  res.send('OK')
})

app.get('/async', (req, res) => {
  asyncCounts += 1
  asyncTest(asyncCounts)
    .then((workerId) => {
      res.status(200)
      res.send(`OK - worker ${workerId}`)
    })
    .catch((error) => {
      res.status(500)
      res.send('Something happened on our end')
    })
})

app.listen(
  3000,
  () => console.log('Example app listening on port 3000!')
)
