import re

p = re.compile('section{([^}]*)}', re.VERBOSE)
print p.sub(r'subsection{\1}','section{First} section{second}')
# ��� : subsection{First} subsection{second}

# replacement �κп� �Լ��� �� �� �ִ�. �� ��� �ſ� ������ ���� ó���� �����ϴ�.
# �Լ��� ���� ���ϰ� ��ġ�� ������ MatchObject �ν��Ͻ��� �Լ��� �����Ѵ�.
# �Լ����� �� �ν��Ͻ��� ����Ͽ� ������ ��, ���ϴ� ���ڿ��� ��ȯ�Ѵ�. 


p = re.compile('section{ (?P<name> [^}]* ) }', re.VERBOSE)
print p.sub(r'subsection{\1}','section{First}')
# 'subsection{First}'
print p.sub(r'subsection{\g<1>}','section{First}')
# 'subsection{First}'
print p.sub(r'subsection{\g<name>}','section{First}')
# 'subsection{First}'
