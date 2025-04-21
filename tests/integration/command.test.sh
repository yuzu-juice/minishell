#!/bin/bash
# 最終的な動作確認用です

. $(dirname $0)/utils/assert.sh

# 一般的な短縮されたコマンド実行
assert_bash_equivalent ls
assert_bash_equivalent "ls | cat"
assert_bash_equivalent "ls | cat | wc -l"

# リダイレクトのテスト
assert_bash_equivalent ls > comand.txt

# 2000cat
assert_bash_equivalent ./tests/integration/utils/2000cat.sh

rm comand.txt
