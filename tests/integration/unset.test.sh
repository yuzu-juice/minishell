#!/bin/bash

. $(dirname $0)/utils/assert.sh

# 存在しない引数でもエラー表示はしない
# assert_stderr 'unset' 'Usage: unset [string]'
# assert_stderr 'unset hoge fuga' 'Usage: unset [string]'
