package inter;
import lexer.*;
import symbols.*;

public class Not extends Logical {

    public Not(Token tok, Expr expr){
	super(tok, expr, expr);
    }

    public void jumping(int t, int f) {
	expr2.jumping(f, t);
    }
    public String toString() {
	return op.toString() + " " + 
	    expr2.toString();
    }
}
