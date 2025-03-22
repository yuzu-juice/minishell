
#!/bin/bash

. $(dirname $0)/utils/assert.sh

assert_bash_equivalent 'pwd'

assert_stderr 'pwd -' 'Usage: pwd'
assert_stderr 'pwd hoge fuga' 'Usage: pwd'
