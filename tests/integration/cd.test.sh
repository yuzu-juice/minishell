#!/bin/bash

. $(dirname $0)/utils/assert.sh

assert_stderr 'cd' 'Usage: cd [relative path | absolute path]'
assert_stderr 'cd ~' '~: No such file or directory'
assert_stderr 'cd ../~' '../~: No such file or directory'
assert_stderr 'cd ...' '...: No such file or directory'
