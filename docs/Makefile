# This is for building the whole site
#
# Mark A. Yoder 12-June-2018

hfiles=$(subst adoc,html,$(wildcard *.adoc))
dirs=$(wildcard 0*)

all: $(hfiles)

%.html:%.adoc
	asciidoctor $^
	