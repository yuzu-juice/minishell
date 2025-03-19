#!/bin/bash

. $(dirname $0)/utils/assert.sh

assert_bash_equivalent 'ls -t'
assert_bash_equivalent '/usr/bin/ls -t'
assert_bash_equivalent 'cat Makefile'
assert_bash_equivalent '/usr/bin/cat Makefile'
