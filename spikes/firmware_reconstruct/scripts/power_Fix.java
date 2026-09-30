// Ghidra post-script (power analysis, run on a private COPY of mp305b_app):
// create functions at tail-call targets and listed addresses, re-fix bodies,
// then decompile every function to <outdir>/app_decomp_fixed.c and index.
// Args: outdir [hexaddr ...]
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.app.cmd.function.CreateFunctionCmd;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.address.*;
import java.io.*;
import java.util.*;

public class power_Fix extends GhidraScript {
    boolean isPush(Instruction i) {
        if (i == null) return false;
        String m = i.getMnemonicString().toLowerCase();
        return m.startsWith("push") || (m.startsWith("stmdb") && i.toString().contains("sp!"));
    }
    boolean isPopNoPc(Instruction i) {
        if (i == null) return false;
        String s = i.toString().toLowerCase();
        return (s.startsWith("pop") || s.startsWith("ldmia sp!")) && !s.contains("pc");
    }
    public void run() throws Exception {
        String[] args = getScriptArgs();
        String out = args[0];
        Listing lst = currentProgram.getListing();
        FunctionManager fm = currentProgram.getFunctionManager();
        Set<Address> targets = new TreeSet<>();
        for (int k = 1; k < args.length; k++) targets.add(toAddr(Long.parseLong(args[k], 16)));
        InstructionIterator it = lst.getInstructions(true);
        while (it.hasNext()) {
            Instruction ins = it.next();
            if (ins.getFlowType().isCall()) {
                for (Address t : ins.getFlows()) targets.add(t);
                continue;
            }
            if (!ins.getFlowType().isJump() || ins.getFlowType().isConditional() || ins.getFlowType().isComputed()) continue;
            Address[] fl = ins.getFlows();
            if (fl.length != 1) continue;
            Address t = fl[0];
            Instruction ti = lst.getInstructionAt(t);
            Instruction prev = lst.getInstructionBefore(ins.getAddress());
            if (isPush(ti) || isPopNoPc(prev)) targets.add(t);
        }
        int made = 0;
        for (Address t : targets) {
            if (fm.getFunctionAt(t) != null) continue;
            if (lst.getInstructionAt(t) == null) disassemble(t);
            if (lst.getInstructionAt(t) == null) continue;
            Function f = createFunction(t, null);
            if (f != null) made++;
        }
        println("created " + made);
        for (Function f : fm.getFunctions(true)) {
            CreateFunctionCmd.fixupFunctionBody(currentProgram, f, monitor);
        }
        DecompInterface di = new DecompInterface();
        di.setOptions(new DecompileOptions());
        di.openProgram(currentProgram);
        PrintWriter c = new PrintWriter(new FileWriter(out + "/app_decomp_fixed.c"));
        PrintWriter idx = new PrintWriter(new FileWriter(out + "/app_functions_fixed.tsv"));
        for (Function f : fm.getFunctions(true)) {
            Set<String> callers = new TreeSet<>();
            for (Function g : f.getCallingFunctions(monitor)) callers.add(g.getEntryPoint().toString());
            Set<String> callees = new TreeSet<>();
            for (Function g : f.getCalledFunctions(monitor)) callees.add(g.getEntryPoint().toString());
            idx.printf("%s\t%d\t%s\t%s%n", f.getEntryPoint(), f.getBody().getNumAddresses(), String.join(",", callers), String.join(",", callees));
            DecompileResults res = di.decompileFunction(f, 120, monitor);
            c.printf("%n// ==== %s @ %s size %d callers [%s]%n", f.getName(), f.getEntryPoint(), f.getBody().getNumAddresses(), String.join(",", callers));
            if (res != null && res.decompileCompleted()) c.println(res.getDecompiledFunction().getC());
            else c.println("// decompile failed");
        }
        c.close(); idx.close();
    }
}
