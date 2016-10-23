#!/bin/sh
# test splitting into 3 chunks

# Copyright (C) 2010-2013 Free Software Foundation, Inc.

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

. "${srcdir=.}/tests/init.sh"; path_prepend_ ./src
print_ver_ split

# N can be greater than the file size
# in which case no data is extracted, or empty files are written
split -n 10 /dev/null || fail=1
test "$(stat -c %s x* | uniq -c | sed 's/^ *//; s/ /x/')" = "10x0" || fail=1
rm x??

# Ensure --elide-empty-files is honored
split -e -n 10 /dev/null || fail=1
stat x?? 2>/dev/null && fail=1

printf '1\n2\n3\n4\n5\n' > in || framework_failure_

split -n 3 in > out || fail=1
split -n 1/3 in > b1 || fail=1
split -n 2/3 in > b2 || fail=1
split -n 3/3 in > b3 || fail=1
printf '1\n2' > exp-1
printf '\n3\n' > exp-2
printf '4\n5\n' > exp-3

compare exp-1 xaa || fail=1
compare exp-2 xab || fail=1
compare exp-3 xac || fail=1
compare exp-1 b1 || fail=1
compare exp-2 b2 || fail=1
compare exp-3 b3 || fail=1
test -f xad && fail=1

Exit $fail
