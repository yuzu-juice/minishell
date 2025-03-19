#!/bin/bash

assert_bash_equivalent() {
	bash_stdout=/tmp/bash_stdout
	minishell_stdout=/tmp/minishell_stdout
	echo "$1" | bash --norc --noprofile > "$bash_stdout"
	expected=$?
	echo "$1" | ./minishell > "$minishell_stdout"
	actual=$?

	# diff stdout
	if diff "$bash_stdout" "$minishell_stdout" >/dev/null; then
		:
	else
		echo "\033[31mFailed: $1\033[0m"
		echo '\033[31mStdouts are different.\033[0m'
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

assert_stderr() {
    minishell_stderr=/tmp/minishell_stderr
    expected=/tmp/expected
    echo "$1" | ./minishell 2> "$minishell_stderr" > /dev/null
    echo "$2" > "$expected"

    # diff stderr
    if diff "$expected" "$minishell_stderr" >/dev/null; then
        :
    else
        echo -e "\033[31mFailed: $1\033[0m"
        echo -e '\033[31mStderrs are different.\033[0m'
        diff "$expected" "$minishell_stderr"
        rm -f "$expected" "$minishell_stderr"
        exit 1
    fi
    rm -f "$expected" "$minishell_stderr"
}
