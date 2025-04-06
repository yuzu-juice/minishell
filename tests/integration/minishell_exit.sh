#!/bin/bash

. $(dirname $0)/utils/assert.sh

assert_stderr 'exit hoge' 'Usage: exit [exit_status]'
assert_stderr 'exit hoge fuga' 'Usage: exit [exit_status]'
