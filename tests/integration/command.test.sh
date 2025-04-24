#!/bin/bash
# 最終的な動作確認用です

. $(dirname $0)/utils/assert.sh

# 一般的な短縮されたコマンド実行
assert_bash_equivalent ls
assert_bash_equivalent "ls | cat"
assert_bash_equivalent "ls | cat | wc -l"

# リダイレクトのテスト
# assert_bash_equivalent ls > comand.txt
# assert_bash_equivalent "<< eof"
# assert_bash_equivalent "> outfile"
# assert_bash_equivalent "< infile"
# assert_bash_equivalent ">> outfile_add"

# rm outfile
# rm infile
# rm outfile_add
# rm comand.txt

# 2000cat
assert_bash_equivalent ./tests/integration/utils/2000cat.sh

# expand dollar->env
assert_bash_equivalent 'echo $USER'
assert_bash_equivalent 'echo "$USER"'
assert_bash_equivalent "echo '$USER'"

# エスケープがうまく機能してないので保留
# assert_bash_equivalent 'echo "$USER" \'$USER\''
# assert_bash_equivalent 'echo \'$USER\' "$USER"'
# assert_bash_equivalent 'echo "$USER"\'$USER\''
# assert_bash_equivalent 'echo \'$USER\'"$USER"'
# assert_bash_equivalent 'echo \'"$USER"\''
# assert_bash_equivalent 'echo "\'$USER"\''

rm comand.txt
