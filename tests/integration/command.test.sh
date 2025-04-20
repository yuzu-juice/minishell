#!/bin/bash

# 動作確認用

# < Makefile cat | cat
# cat | cat | cat
# 2000cat.sh



# env -i ＜＞ 環境変数を渡さずに実行できる

# <<must>>
# minishell> ^C
# minishell>
# exit
# c6r3s7% echo $?
# 0

# minishell> << eof //ほかリダイレクト記号も同様
# zsh: segmentation fault (core dumped)  ./minishell
# c6r3s7% ./minishell

# exit "   42"
# Usage: exit [exit_status]. 	numeric argument required

# PATH がないときに、コマンドエラーがでない

# export のキー側のバリデーションがきかない

# minishell> echo "$USER"'$USER'
# yohatanayohatana

# minishell> 'l's
# No such file or directory
# cmd: 'l's
# minishell> "l"s
# No such file or directory
# cmd: "l"s

# minishell> export =./:$PATH
# minishell> echo $PATH
# /home/yohatana/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin

# minishell> echo -nnnnn
# -nnnnn
# minishell> echo -n -n
# -nminishell>


# <<want>>
# minishell> echo | echo |
# syntax_error
# syntax_error
