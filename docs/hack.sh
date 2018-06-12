#!/bin/bash
# Rebuilds all the html files
for dir in 0* ; do
    echo $dir
    cd $dir
    asciidoctor ${dir:2}.adoc
    cd ..
done
