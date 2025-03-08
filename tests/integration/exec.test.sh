source $(dirname $0)/utils/assert.sh

assert 'ls'
assert 'ls -l'
assert '/usr/bin/ls'
assert 'cat Makefile'
assert 'echo aaa sss ddd'
