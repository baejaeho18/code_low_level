#!/usr/bin/env python
#encoding: utf-8

# back reference

# etc : 
#       '.*[.].*$' -> �߰��� �� �ϳ��̻��� ������ ��Ʈ�� leech.doc

import re;

p = re.compile(r'(\b\w+)\s+\1');

print p.search('Paris in i i the the a a spring').group();

p = re.compile(r'(?P<word>\b\w+)\s+(?P=word)')
print p.search('Paris in the the spring').group()

p = re.compile("[^\(]*(\(.*\))[^\)]*")
print p.search('create table kakao (id INT, data varchar(100));').groups()
