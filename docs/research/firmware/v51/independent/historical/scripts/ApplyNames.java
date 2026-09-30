// Apply names/*.tsv (addr<TAB>name<TAB>comment) to the program given by script arg 0 (app|ch58x|pd8051).
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.nio.file.*;
public class ApplyNames extends GhidraScript {
    public void run() throws Exception {
        String tag = getScriptArgs()[0];
        File dir = new File(System.getProperty("user.home") + "/mp305b-fw-re/names");
        int n = 0;
        for (File f : dir.listFiles()) {
            if (!f.getName().startsWith(tag + "_") || !f.getName().endsWith(".tsv")) continue;
            for (String line : Files.readAllLines(f.toPath())) {
                if (line.startsWith("#") || line.isBlank()) continue;
                String[] p = line.split("\t");
                if (p.length < 2) continue;
                Address a;
                try { a = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(p[0].trim().replace("0x", "")); } catch (Exception e) { continue; }
                String nm = p[1].trim().replaceAll("[^A-Za-z0-9_]", "_");
                Function fn = getFunctionAt(a);
                try {
                    if (fn != null) fn.setName(nm, SourceType.USER_DEFINED);
                    else currentProgram.getSymbolTable().createLabel(a, nm, SourceType.USER_DEFINED);
                    if (p.length > 2 && !p[2].isBlank()) setPlateComment(a, p[2]);
                    n++;
                } catch (Exception e) { println("skip " + line + " : " + e.getMessage()); }
            }
        }
        println("APPLIED " + n);
    }
}
