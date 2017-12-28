{
  "targets": [
    {
      "include_dirs" : [
        "<!(node -e \"require('nan')\")"
      ],
      "target_name": "async",
      "sources": [ "async.cc", "order.cc", "worker.cc", "order_helper.cc" ]
    }
  ]
}