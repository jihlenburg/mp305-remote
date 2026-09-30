// Ghidra post-script: export decompiled C for every function, a function index and strings.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.address.*;
import java.io.*;
import java.util.*;

public class Export extends GhidraScript {
    public void run() throws Exception {
        String tag = getScriptArgs().length > 0 ? getScriptArgs()[0] : "app";
        String out = System.getProperty("user.home") + "/mp305b-fw-re/out/";
        DecompInterface di = new DecompInterface();
        DecompileOptions opt = new DecompileOptions();
        di.setOptions(opt);
        di.openProgram(currentProgram);
        FunctionManager fm = currentProgram.getFunctionManager();
        ReferenceManager rm = currentProgram.getReferenceManager();
        PrintWriter c = new PrintWriter(new FileWriter(out + tag + "_decomp.c"));
        PrintWriter idx = new PrintWriter(new FileWriter(out + tag + "_functions.tsv"));
        idx.println("addr\tname\tsize\tncallers\tcallers\tcallees");
        int n = 0, fail = 0;
        for (Function f : fm.getFunctions(true)) {
            if (monitor.isCancelled()) break;
            Set<String> callers = new TreeSet<>();
            for (Function g : f.getCallingFunctions(monitor)) callers.add(g.getEntryPoint().toString());
            Set<String> callees = new TreeSet<>();
            for (Function g : f.getCalledFunctions(monitor)) callees.add(g.getName());
            idx.printf("%s\t%s\t%d\t%d\t%s\t%s%n", f.getEntryPoint(), f.getName(), f.getBody().getNumAddresses(),
                callers.size(), String.join(",", callers), String.join(",", callees));
            DecompileResults res = di.decompileFunction(f, 120, monitor);
            c.printf("%n// ==== %s @ %s size %d callers [%s]%n", f.getName(), f.getEntryPoint(), f.getBody().getNumAddresses(), String.join(",", callers));
            if (res != null && res.decompileCompleted()) c.println(res.getDecompiledFunction().getC());
            else { c.println("// decompile failed: " + (res == null ? "null" : res.getErrorMessage())); fail++; }
            n++;
        }
        c.close(); idx.close();
        PrintWriter s = new PrintWriter(new FileWriter(out + tag + "_strings.tsv"));
        for (Data d : currentProgram.getListing().getDefinedData(true)) {
            if (!d.hasStringValue()) continue;
            Set<String> xr = new TreeSet<>();
            for (Reference r : rm.getReferencesTo(d.getAddress())) {
                Function g = fm.getFunctionContaining(r.getFromAddress());
                xr.add(g == null ? r.getFromAddress().toString() : g.getName());
            }
            s.printf("%s\t%s\t%s%n", d.getAddress(), String.valueOf(d.getValue()).replace("\n", "\\n").replace("\t", "\\t"), String.join(",", xr));
        }
        s.close();
        println("EXPORT functions=" + n + " failed=" + fail);
    }
}
