# ���ϵ� 

 example02.ll 

  - lex ����
  - ��ū�� ���� 

 example02.yy 

  - bison (yacc) ���� 
  - ���� ���� ���� 

# ���α׷� ���� 

 flex --wincompat -o example_lexer.cpp examle02.ll  

 bison -d --verbose  -o example_parser.cpp example02.yy 

 -d �ɼ��� ����ϸ� ��� ������ ������. 

 flex ������� ���ؼ��� -d �ɼ� �߰� 

 ����: ���� �������� �� .ll, .yy ������ �;� ��

# ������ ���� ���� 

 ������Ʈ�� example_lexer.cpp, example_parser.cpp, example_parser.hpp�� �߰�

 �߰��� .cpp ���ϵ鿡 �̸� �����ϵ� ��� ��� ���� �ɼ� ����

  
# ���� 

 example02.ll ���Ͽ� main �Լ� ���� 
 
 ./parser.exe �������
 
 ���� ���� �����ϸ� ��� ����� print ������ Ȯ�� ���� 
 
     


