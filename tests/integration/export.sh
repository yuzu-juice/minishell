#!/bin/bash

. $(dirname $0)/utils/assert.sh

assert_stderr 'export hoge fuga' 'Usage: export [key=value]'
