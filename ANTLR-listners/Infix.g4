grammar Infix;

start 	: 	list END;
list 	:	stmt list
		|;

stmt	:	expr ';';

expr	:	term # ExprSingle
		|	term op='+' term # ExprMulti
		|	term op='-' term # ExprMulti;

term	:	factor # TermSingle
		|	factor op='*' factor # TermMulti
		|	factor op='/' factor # TermMulti
		|	factor op=MOD factor # TermMulti;

factor	:	'(' expr ')' # FactorExpr
		|	ID # FactorId
		|	NUM # FactorNum ;

MOD 	:	'MOD';
END 	:	'EOF';
ID 	 	:	LETTER (LETTER|DIGIT)*;
NUM 	:	DIGIT+;

LETTER	:	[A-Za-z];
DIGIT	: 	[0-9];
SPACE 	: 	[ \t\r\n]+ -> skip;
