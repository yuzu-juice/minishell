. $(dirname $0)/utils/assert.sh

assert 'ls -t'
assert '/usr/bin/ls -t'
assert 'cat Makefile'
assert '/usr/bin/cat Makefile'
assert 'echo'
assert 'echo aaa'
assert 'echo "aaa"sss "ddd"'
assert 'echo \'aaa\' \'sss\' \'ddd\''
assert 'echo aaa sss        ddd'
