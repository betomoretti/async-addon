const nativeTest = require('./lib/native_buffer')

nativeTest(0)
  .then((workerId) => {
    console.info(workerId)
    // res.status(200)
    // res.send(`OK - worker ${workerId}`)
  })
  .catch((error) => {
    console.error(error)
    // res.status(500)
    // res.send('Something happened on our end')
  })