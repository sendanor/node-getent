{
  "targets": [
    {
      "target_name": "getent",
      "sources": [ "getent.cc" ],
      "include_dirs" : ["<!(node -e \"require('nan')\")"],
    }
  ]
}
