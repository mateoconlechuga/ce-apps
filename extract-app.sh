#!/bin/bash

# example: ./extract-app.sh transfrm.8ek transfrm.bin

dd if=$1 of=$2 bs=1 skip=78
truncate --size=-260 $2

