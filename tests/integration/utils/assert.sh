assert() {
	bash_stdout=/tmp/bash_stdout
	minishell_stdout=/tmp/minishell_stdout
	echo "$1" | bash --norc --noprofile > "$bash_stdout"  2>/dev/null
	expected=$?
	echo "$1" | ./minishell > "$minishell_stdout" 2>/dev/null
	actual=$?

	# diff stdout
	if diff "$bash_stdout" "$minishell_stdout" >/dev/null; then
		:
	else
		echo "\033[31mFailed: $1\033[0m"
		echo '\033[31mStdouts are different.\033[0m"'
		diff "$bash_stdout" "$minishell_stdout"
		rm -f "$bash_stdout" "$minishell_stdout"
		exit 1
	fi
	rm -f "$bash_stdout" "$minishell_stdout"

	# diff exit status
	if [ "$actual" = "$expected" ]; then
		:
	else
		echo "\033[31mFailed: $1\033[0m"
		echo "\033[31mExpected exit status is $expected but got $actual\033[0m"
		exit 1
	fi
}

