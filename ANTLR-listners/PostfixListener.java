import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.util.*;

public class PostfixListener extends InfixBaseListener {
	Hashtable<String, Integer> symbols;

	public PostfixListener() {
		symbols = new Hashtable<>();
	}

	@Override 
	public void enterStart(InfixParser.StartContext ctx) { }
	@Override 
	public void exitStart(InfixParser.StartContext ctx) {
		System.out.println("EOF");
		System.out.print("Symbols: ");
		List<String> symbolList = new ArrayList<String>();
		for (String key : symbols.keySet()) {
			symbolList.add(key + ":" + symbols.get(key));
		}
		System.out.println(String.join(", ", symbolList));
	}
	@Override
	public void exitStmt(InfixParser.StmtContext ctx) {
		System.out.println(";");
	}
	@Override 
	public void enterExprMulti(InfixParser.ExprMultiContext ctx) {
		ParseTree leftChild = ctx.getChild(0);
		if (leftChild.getChildCount() == 1) {
			// if is a terminal node
			System.out.print(leftChild.getText() + " ");
		}
	}
	@Override
	public void exitExprMulti(InfixParser.ExprMultiContext ctx) {
		ParseTree rightChild = ctx.getChild(2);
		if (rightChild.getChildCount() == 1) {
			// if is a terminal node
			System.out.print(rightChild.getText() + " ");
		}
		// print the operator in post-order
		System.out.print(ctx.op.getText() + " ");
	}
	@Override
	public void enterTermMulti(InfixParser.TermMultiContext ctx) {
		ParseTree leftChild = ctx.getChild(0);
		if (leftChild.getChildCount() == 1) {
			// if is a terminal node
			System.out.print(leftChild.getText() + " ");
		}
	}
	@Override
	public void exitTermMulti(InfixParser.TermMultiContext ctx) {
		ParseTree rightChild = ctx.getChild(2);
		if (rightChild.getChildCount() == 1) {
			// if is a terminal node
			System.out.print(rightChild.getText() + " ");
		}
		// print the operator in post-order
		System.out.print(ctx.op.getText() + " ");
	}
	@Override public void exitFactorId(InfixParser.FactorIdContext ctx) {
		if (!symbols.contains(ctx.getText()))
			symbols.put(ctx.getText(), ctx.getStart().getLine());
	}

}
