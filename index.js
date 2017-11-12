const async = require('bindings')('async')



console.log(async.DoIt(() => {
  console.log("Corri desde adentro papa")
}))
