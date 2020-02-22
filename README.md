# minishell
[![Build Status](https://travis-ci.com/lgutter/minishell.svg?branch=master)](https://travis-ci.com/lgutter/minishell) [![codecov](https://codecov.io/gh/lgutter/minishell/branch/master/graph/badge.svg)](https://codecov.io/gh/lgutter/minishell)

Minishell is a project in the [Codam](https://www.codam.nl/) curriculum requiring you to build a shell with minimum functionality.

This shell can handle environment variables (including expansions), command execution, and a small set of builtins.

# Compiling
Compilation has been tested om MacOS Mojave, Debian, and Ubuntu, and requires `gcc` and `make`.

To compile the shell, run `make`.

Optionally, you can install [Criterion](https://github.com/Snaipe/Criterion) and run `make test` to compile a limited set of tests. You can run these tests with `./tests/minitest`.
If you also want to see coverage reports, run `make fclean && make test CV=1` to compile with coverage flags, and run `make gcov` to generate coverage reports of the source files.

# Usage
To start the shell, run `./minishell`.

This shell can handle basic variable expansion, but quotes are not handled at all.
Any command found in the `PATH` will be executed, and the shell has the following builtins:

- `cd` (including `cd -` )
- `echo` (without any extra options)
- `env` (without any arguments or options)
- `setenv` (accepting 2 arguments: `key` and `value`)
- `unsetenv` (will attempt to unset ALL keys given as arguments)
- `exit` (accepts a numerical first arguments, anything else is ignored, will ALWAYS exit.)

minishell will initialize a very minimal environment if it receives an empty environment.

