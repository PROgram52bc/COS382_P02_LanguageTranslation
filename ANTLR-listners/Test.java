import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.FileInputStream;
import java.io.InputStream;
public class Test {
	public static void main(String[] args) throws Exception {
		String inputFile = "../test.txt";
		if (args.length > 0) inputFile = args[0];
		InputStream is = System.in;
		if (inputFile != null) is = new FileInputStream(inputFile);
		System.out.println(inputFile);
		CharStream input = CharStreams.fromStream(is);
		InfixLexer lexer = new InfixLexer(input);
		CommonTokenStream tokens = new CommonTokenStream(lexer);
		InfixParser parser = new InfixParser(tokens);
		ParseTree tree = parser.start();
		ParseTreeWalker walker = new ParseTreeWalker();
		PostfixListener postfix = new PostfixListener();
		walker.walk(postfix, tree);
	}
}

