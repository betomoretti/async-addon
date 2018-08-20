{
  "targets": [
    {
      "include_dirs" : [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      "target_name": "async",
      "sources": [
        "src/order_helper.cc",
        "src/async.cc",
        "src/order.cc",
        "src/worker_buffer.cc",
        "src/worker_classes.cc" ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }
  ]
}