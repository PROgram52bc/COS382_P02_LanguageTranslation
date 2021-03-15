grammar InfixActions;

start 	
		locals [
		List<String> symbols = new ArrayList<>();
		]
		: 	list END { System.out.println("eof\nSymbols: "+$start::symbols); };

list 	:	expr ';' { System.out.print(";\n"); } list
		|;
expr	:	term terms;
terms	:	'+' term { System.out.print("+ "); } terms
		|	'-' term { System.out.print("- "); } terms
		|;
term	:	factor factors;
factors	:	'*' factor { System.out.print("* "); } factors
		|	'/' factor { System.out.print("/ "); } factors
		|	MOD factor { System.out.print("MOD "); } factors
		|;
factor	:	'(' expr ')'
		|	id=ID { 
			System.out.print($id.text + " ");
			$start::symbols.add($id.text);
		}
		|	num=NUM { System.out.print($num.text + " "); };

MOD 	:	'MOD';
END 	:	'EOF';
ID 	 	:	LETTER (LETTER|DIGIT)*;
NUM 	:	DIGIT+;

LETTER	:	[A-Za-z];
DIGIT	: 	[0-9];
SPACE 	: 	[ \t\r\n]+ -> skip;
