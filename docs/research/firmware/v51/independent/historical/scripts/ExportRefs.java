// Export every reference (from, function, to, type) to a TSV.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
public class ExportRefs extends GhidraScript {
    public void run() throws Exception {
        String tag = getScriptArgs()[0];
        PrintWriter w = new PrintWriter(new FileWriter(System.getProperty("user.home") + "/mp305b-fw-re/out/" + tag + "_refs.tsv"));
        w.println("from\tfunc\tto\ttoname\ttype");
        FunctionManager fm = currentProgram.getFunctionManager();
        SymbolTable st = currentProgram.getSymbolTable();
        for (Reference r : currentProgram.getReferenceManager().getReferenceIterator(currentProgram.getMinAddress())) {
            Function f = fm.getFunctionContaining(r.getFromAddress());
            Symbol s = st.getPrimarySymbol(r.getToAddress());
            w.printf("%s\t%s\t%s\t%s\t%s%n", r.getFromAddress(), f == null ? "" : f.getName() + "@" + f.getEntryPoint(), r.getToAddress(), s == null ? "" : s.getName(), r.getReferenceType());
        }
        w.close();
    }
}
