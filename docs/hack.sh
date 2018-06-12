#!/bin/bash
# Rebuilds all the html files
for dir in 0* ; do
    echo $dir
    asciidoctor ${dir:2}.adoc
    cd ..
done
