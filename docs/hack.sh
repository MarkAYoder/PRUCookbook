#!/bin/bash
# Rebuilds all the html files

asciidoctor -v index.adoc

for dir in 0* ; do
    echo $dir
    cd $dir
    asciidoctor -v ${dir:2}.adoc
    cd ..
done
