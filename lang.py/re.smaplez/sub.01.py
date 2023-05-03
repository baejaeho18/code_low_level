#!/usr/local/bin/python

import re;
"""
  patterm.sub(replace, source);

  �� source string ���� pattern�� ��Ī�ϴ�  expression�� replace�� �ٲپ��
"""

p = re.compile( '(blue|white|red)');
print p.sub('colour', 'blue socks and red shoes');
print p.sub('colour', 'blue socks and red shoes', 1);

"""
result:
colour socks and colour shoes
colour socks and red shoes
"""


"""
empty matching exam
"""
p = re.compile('x*')
print p.sub('-', 'abxd')

"""
result:
-a-b--d-
"""
