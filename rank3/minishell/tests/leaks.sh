#!/bin/bash

# Running Valgrind with full debugging options
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=tests/suppressions.supp ./bin/minishell