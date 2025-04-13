
# Make x86-64 random byte generators.

# Copyright 2015, 2020, 2021 Paul Eggert

# This program is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

# Optimization level.  Change this -O2 to -Og or -O0 or whatever.
OPTIMIZE =

#Run with BASH
SHELL := /bin/bash

# The C compiler and its options.
CC = gcc
CFLAGS = $(OPTIMIZE) -g3 -Wall -Wextra -fanalyzer \
  -march=native -mtune=native -mrdrnd

# The archiver command, its options and filename extension.
TAR = tar
TARFLAGS = --gzip --transform 's,^,randall/,'
TAREXT = tgz

default: randall

# Relevant files.
FILES = $(options.c) $(options.h)

randall: randall.c options.c rand64-hw.c
	$(CC) $(CFLAGS) randall.c options.c rand64-hw.c rand64-sw.c output.c -o randall
#	$(CC) $(CFLAGS) $@.c -o $@

assignment: randall-assignment.$(TAREXT)
assignment-files = COPYING Makefile randall.c
randall-assignment.$(TAREXT): $(assignment-files)
	$(TAR) $(TARFLAGS) -cf $@ $(assignment-files)

submission-tarball: randall-submission.$(TAREXT)
submission-files = $(assignment-files) \
  notes.txt options.c options.h output.c output.h rand64-hw.c rand64-hw.h rand64-sw.h rand64-sw.c# More files should be listed here, as needed.
randall-submission.$(TAREXT): $(submission-files)
	$(TAR) $(TARFLAGS) -cf $@ $(submission-files)

repository-tarball:
	$(TAR) -czf randall-git.tgz .git

.PHONY: default clean assignment submission-tarball repository-tarball

clean:
	rm -f *.o *.$(TAREXT) randall

# Unit test that checks NBYTES
check: randall
	@echo "Running test cases..."
	@echo "=========== TEST 1 ==========="
#@./randall 20 | wc -c | (grep -q "^20$" && echo "PASSED") || (echo "FAILED" && false)
	@if ./randall 20 | wc -c | grep -q "^20$$"; then \
            echo "PASSED"; \
        else \
            echo "FAILED"; exit 1; \
        fi
# Checks for correctly producing 20 bytes in 5 byte sections
	@echo "=========== TEST 2 ===========" 
	@if ./randall -o 5 20 | wc -c | grep -q "^20$$"; then \
            echo "PASSED"; \
        else \
            echo "FAILED"; exit 1; \
        fi

# Checks for invalid negative numbers
	@echo "=========== TEST 3 ==========="
	@if ./randall -10 2>/dev/null; then \
            echo "FAILED"; exit 1; \
        else \
            echo "PASSED"; \
        fi