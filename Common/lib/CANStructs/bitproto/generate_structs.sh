#!/bin/sh

for file in messages/*; do
    bitproto c $file structs
done
