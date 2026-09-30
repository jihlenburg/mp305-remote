// Original instructions request reset and then spin. Mark those paths as
// non-returning so the decompiler cannot merge the following flash routines.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.SourceType;

public class RecoveryFixups extends GhidraScript {
    public void run() throws Exception {
        long[] entries = {0x1feb8, 0x1fc86, 0x1b71c};
        String[] names = {"system_reset", "boot_mailbox_then_reset", "system_reset_to_boot"};
        for (int i = 0; i < entries.length; i++) {
            Function f = getFunctionAt(toAddr(entries[i]));
            if (f == null) throw new IllegalStateException("Missing reset function " + entries[i]);
            f.setNoReturn(true);
            f.setName(names[i], SourceType.USER_DEFINED);
            setPlateComment(f.getEntryPoint(), "Non-returning reset path. Original instructions reach AIRCR SYSRESETREQ at 0x1FEC8. Offline write trace checks the boot mailbox and AIRCR; no hardware reset was performed.");
        }
        println("RESET_FIXUPS 3");
    }
}
