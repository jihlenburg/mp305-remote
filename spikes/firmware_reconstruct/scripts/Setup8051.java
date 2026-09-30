// Ghidra pre-script for the 8051 slice: seed functions from the LJMP vector table.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.symbol.*;
public class Setup8051 extends GhidraScript {
    public void run() throws Exception {
        AddressSpace code = currentProgram.getAddressFactory().getAddressSpace("CODE");
        int[] vec = {0x00,0x03,0x0B,0x13,0x1B,0x23,0x2B,0x33,0x3B,0x43,0x4B,0x53,0x5B,0x63,0x6B,0x73,0x7B,0x83,0x8B,0x93};
        for (int v : vec) {
            Address va = code.getAddress(0x1000 + v);
            int op = currentProgram.getMemory().getByte(va) & 0xFF;
            currentProgram.getSymbolTable().createLabel(va, String.format("VEC_%02X", v), SourceType.USER_DEFINED);
            if (op != 0x02) continue;
            int t = ((currentProgram.getMemory().getByte(va.add(1)) & 0xFF) << 8) | (currentProgram.getMemory().getByte(va.add(2)) & 0xFF);
            println(String.format("vector %02X -> %04X", v, t));
            if (t < 0x1000 || t >= 0xBA00) continue;
            Address ta = code.getAddress(t);
            currentProgram.getSymbolTable().createLabel(ta, String.format("ISR_%02X", v), SourceType.USER_DEFINED);
            disassemble(ta);
            try { createFunction(ta, null); } catch (Exception e) { }
        }
    }
}
