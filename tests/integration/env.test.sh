#!/bin/bash

. $(dirname $0)/utils/assert.sh

# envの内容、minishell起動時に変わっちゃうのでbashとの単純な比較はしない

assert_stderr 'env hoge' 'Usage: env'
assert_stderr 'env hello hoge' 'Usage: env'
