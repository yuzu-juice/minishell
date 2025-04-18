#!/bin/bash

. $(dirname $0)/utils/assert.sh

assert_bash_equivalent 'echo -n'
assert_bash_equivalent 'echo -n aaa'
assert_bash_equivalent 'echo -n "aaa"sss "ddd"'
assert_bash_equivalent 'echo -n "aaa sss"'
assert_bash_equivalent "echo -n 'aaa sss'"
assert_bash_equivalent "echo -n 'aaa' 'sss' 'ddd'"
assert_bash_equivalent 'echo -n aaa sss        ddd'
assert_bash_equivalent "echo -n 'single quoted' mixed \"double quoted\""

assert_stderr 'echo' 'Usage: echo -n [string]...'
assert_stderr 'echo hello' 'Usage: echo -n [string]...'
assert_stderr 'echo -x test' 'Usage: echo -n [string]...'
assert_stderr 'echo -nx test' 'Usage: echo -n [string]...'
assert_stderr 'echo -n-n test' 'Usage: echo -n [string]...'
