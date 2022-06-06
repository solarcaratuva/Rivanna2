#!/bin/bash

# TODO: Account for new location of .h struct files
for file in messages/*; do
    cantools generate_c_source -o structs $file
done
