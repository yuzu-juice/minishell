#!/bin/bash

. $(dirname $0)/utils/assert.sh

assert_stderr 'unset' 'Usage: unset [string]'
assert_stderr 'unset hoge fuga' 'Usage: unset [string]'
