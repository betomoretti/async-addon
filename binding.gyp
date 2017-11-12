{
  "targets": [
    {
      "include_dirs" : [
        "<!(node -e \"require('nan')\")"
      ],
      "target_name": "async",
      "sources": [ "async.cc" ]
    }
  ]
}