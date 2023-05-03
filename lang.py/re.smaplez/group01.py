#!/usr/local/bin/python

"""
    group�� regular expression���� ��ȣ�� ���� sub-expression�̴�.
"""
import re

match = re.match(r"(?P<int>\d+)\.(\d*)", '3.14')
print match.group(1), match.group(2)
print match.group(1, 2)
print match.groups()
print match.groupdict(int)
print match.string[match.start(2):match.end(2)]

"""
result :
3 14
('3', '14')
('3', '14')
{'int': '3'}
14
"""
