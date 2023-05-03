#!/usr/bin/env python

import os
import glob
import re
import string
import sys

p = re.compile('(.*)[.](cxx)$')

path = '*'
for i in glob.glob(path):
  m = p.match(i)
    if m:
      s1, s2 = m.group(1), m.group(2)
      oldname = s1 + '.' + s2
      newname = s1 + '.cpp'
      os.renames(oldname, newname)
      print s1, s2
