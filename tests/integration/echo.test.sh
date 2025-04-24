#!/bin/bash

. $(dirname $0)/utils/assert.sh

assert_bash_equivalent 'echo -n'
assert_bash_equivalent 'echo -n aaa'
assert_bash_equivalent 'echo -n "aaa"sss "ddd"'
assert_bash_equivalent 'echo -n "aaa   sss"'
assert_bash_equivalent "echo -n 'aaa   sss'"
assert_bash_equivalent "echo -n 'aaa' 'sss' 'ddd'"
assert_bash_equivalent 'echo -n aaa sss        ddd'
assert_bash_equivalent "echo -n 'single quoted' mixed \"double quoted\""

assert_bash_equivalent 'echo'
assert_bash_equivalent 'echo aaa'
assert_bash_equivalent 'echo "aaa"sss "ddd"'
assert_bash_equivalent 'echo "aaa   sss"'
assert_bash_equivalent "echo 'aaa   sss'"
assert_bash_equivalent "echo 'aaa' 'sss' 'ddd'"
assert_bash_equivalent 'echo aaa sss        ddd'
assert_bash_equivalent "echo 'single quoted' mixed \"double quoted\""

# delete
# reason: echo only allowed
# assert_stderr 'echo' 'Usage: echo -n [string]...'
# assert_stderr 'echo hello' 'Usage: echo -n [string]...'
# assert_stderr 'echo -x test' 'Usage: echo -n [string]...'
# assert_stderr 'echo -nx test' 'Usage: echo -n [string]...'
# assert_stderr 'echo -n-n test' 'Usage: echo -n [string]...'
