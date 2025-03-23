#!/bin/bash

. $(dirname $0)/utils/assert.sh

assert_bash_equivalent 'env'

assert_stderr 'env hoge' 'Usage: env'
assert_stderr 'env hello hoge' 'Usage: env'
