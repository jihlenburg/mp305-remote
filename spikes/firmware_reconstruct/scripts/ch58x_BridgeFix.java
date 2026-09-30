// Ghidra script (run on a COPY of mp305b_ch58x): add missed functions, label the
// WCH BLE library jump table at 0x40000, then export decompiled C of all functions.
// args: <libnames.tsv> <out.c>
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.data.*;
import java.io.*;
import java.nio.file.*;
import java.util.*;

public class ch58x_BridgeFix extends GhidraScript {
    public void run() throws Exception {
        String[] a = getScriptArgs();
        Memory mem = currentProgram.getMemory();
        SymbolTable st = currentProgram.getSymbolTable();
        Listing lst = currentProgram.getListing();
        if (!mem.contains(toAddr(0x40000))) {
            MemoryBlock b = mem.createUninitializedBlock("BLE_LIB_TABLE", toAddr(0x40000), 0x300, false);
            b.setWrite(false);
        }
        for (String line : Files.readAllLines(Paths.get(a[0]))) {
            String[] f = line.trim().split("\t");
            if (f.length < 2) continue;
            long ad = Long.parseLong(f[0], 16);
            try { st.createLabel(toAddr(ad), "p_" + f[1], SourceType.USER_DEFINED); } catch (Exception e) {}
            try { lst.createData(toAddr(ad), PointerDataType.dataType); } catch (Exception e) {}
        }
        long[] extra = {0x2ab6, 0x2b38, 0x2d8c, 0x2e28, 0x2f58, 0x56c0, 0x56c2, 0x56fe, 0x698c, 0x6c76, 0x6cae, 0x7104};
        for (long e : extra) {
            try { disassemble(toAddr(e)); } catch (Exception ex) {}
            if (getFunctionAt(toAddr(e)) == null) {
                try { createFunction(toAddr(e), null); } catch (Exception ex) { println("fail " + Long.toHexString(e)); }
            }
        }
        DecompInterface di = new DecompInterface();
        di.setOptions(new DecompileOptions());
        di.openProgram(currentProgram);
        PrintWriter c = new PrintWriter(new FileWriter(a[1]));
        for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
            DecompileResults res = di.decompileFunction(f, 120, monitor);
            c.printf("%n// ==== %s @ %s size %d%n", f.getName(), f.getEntryPoint(), f.getBody().getNumAddresses());
            if (res != null && res.decompileCompleted()) c.println(res.getDecompiledFunction().getC());
            else c.println("// decompile failed");
        }
        c.close();
    }
}
