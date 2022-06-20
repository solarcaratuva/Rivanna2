#!/bin/bash

# TODO: Account for new location of .h struct files
for file in messages/*.dbc; do
    cantools generate_c_source -o structs $file
done
