#!/usr/local/bin/python

import re;
"""
pattern.split(string)  : string�� ��õ� pattern�� �°� �߶� sub-string list�� ����

\W == [^a-zA-Z0-9] �� ���Ĵ��޸��� �ƴ� �ϳ��� ����
"""

p1 = re.compile(r'\W+')
p2 = re.compile(r'(\W+)')

print p1.split('This... is a test.')
print p2.split('This... is a test.')
"""
['This', 'is', 'a', 'test', '']
['This', '... ', 'is', ' ', 'a', ' ', 'test', '.', '']
"""

print re.split('[\W]+',   'Words, words, words.')
print re.split('([\W]+)', 'Words, words, words.')
"""
['Words', 'words', 'words', '']
['Words', ', ', 'words', ', ', 'words', '.', '']
"""
