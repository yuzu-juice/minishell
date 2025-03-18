. $(dirname $0)/utils/assert.sh

assert 'ls -t'
assert '/usr/bin/ls -t'
assert 'cat Makefile'
assert '/usr/bin/cat Makefile'
assert 'echo -n'
assert 'echo -n aaa'
assert "echo -n 'aaa' 'sss' 'ddd'"
assert 'echo -n aaa sss        ddd'
