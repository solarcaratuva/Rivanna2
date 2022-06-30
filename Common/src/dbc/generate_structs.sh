#!/bin/bash

for file in messages/*.dbc; do
    cantools generate_c_source -o structs $file
done
mv structs/*.h ../../include/dbc/structs/
