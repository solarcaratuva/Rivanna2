#!/bin/bash

for file in messages/*; do
    cantools generate_c_source -o structs $file
done
