#!/bin/bash

# example: ./extract-app.sh transfrm.8ek transfrm.sig

tail -c 256 $1 > $2

