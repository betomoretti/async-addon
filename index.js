// process.env.UV_THREADPOOL_SIZE = Math.ceil(Math.max(4, require('os').cpus().length * 1.5));

const workerTest = require('./lib/worker')
const instancesTest = require('./lib/instances')
const buffersTest = require('./lib/buffers')
const express = require('express')
const app = express()
let syncCounts = 0
let asyncCounts = 0

app.get('/worker', (req, res) => {
  syncCounts += 1
  workerTest(syncCounts)
  res.status(200)
  res.send('OK')
})

app.get('/instances', (req, res) => {
  asyncCounts += 1
  instancesTest(asyncCounts)
    .then((workerId) => {
      res.status(200)
      res.send(`OK - worker ${workerId}`)
    })
    .catch((error) => {
      res.status(500)
      res.send('Something happened on our end')
    })
})

app.get('/buffers', (req, res) => {
  asyncCounts += 1
  buffersTest(asyncCounts)
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
