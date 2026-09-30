// Ghidra pre-script for the CH58x slice (data.bin+0xB000), linked at 0x1000.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.mem.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.*;
import java.io.*;
import java.nio.file.*;
import java.util.*;

public class SetupCH58x extends GhidraScript {
    static final String RE = System.getProperty("user.home") + "/mp305b-fw-re/";
    public void run() throws Exception {
        Memory mem = currentProgram.getMemory();
        SymbolTable st = currentProgram.getSymbolTable();
        Listing lst = currentProgram.getListing();
        byte[] img = Files.readAllBytes(Paths.get(RE + "bin/ch58x.bin"));
        // RAM: 0x20000000..0x20002000 uninit, highcode copy, data copy, bss.
        MemoryBlock b;
        for (MemoryBlock fb : mem.getBlocks()) { fb.setWrite(false); fb.setExecute(true); fb.setName("FLASH"); }
        b = mem.createUninitializedBlock("RAM_LO", toAddr(0x20000000L), 0x2000, false); b.setWrite(true);
        byte[] hc = Arrays.copyOfRange(img, 0x8, 0xC48);
        b = mem.createInitializedBlock("RAM_HIGHCODE", toAddr(0x20002000L), new ByteArrayInputStream(hc), hc.length, monitor, false);
        b.setWrite(true); b.setExecute(true);
        byte[] dt = Arrays.copyOfRange(img, 0x8318, 0x8628);
        b = mem.createInitializedBlock("RAM_DATA", toAddr(0x20002C40L), new ByteArrayInputStream(dt), dt.length, monitor, false);
        b.setWrite(true);
        b = mem.createUninitializedBlock("RAM_BSS", toAddr(0x20002F50L), 0x20008000L - 0x20002F50L, false); b.setWrite(true);
        b = mem.createUninitializedBlock("JUMP_IAP", toAddr(0x0), 0x1000, false);
        b = mem.createUninitializedBlock("PERIPH", toAddr(0x40001000L), 0xF000, false); b.setWrite(true); b.setVolatile(true);
        b = mem.createUninitializedBlock("PFIC", toAddr(0xE000E000L), 0x1000, false); b.setWrite(true); b.setVolatile(true);
        for (String line : Files.readAllLines(Paths.get(RE + "out/ch58x_regs.txt"))) {
            String[] f = line.trim().split(" ");
            long ad = Long.parseLong(f[0], 16);
            if (!mem.contains(toAddr(ad))) continue;
            st.createLabel(toAddr(ad), f[2], SourceType.IMPORTED);
            DataType d = f[1].equals("1") ? ByteDataType.dataType : f[1].equals("2") ? WordDataType.dataType : DWordDataType.dataType;
            try { lst.createData(toAddr(ad), d); } catch (Exception ex) { }
        }
        // Vector table in RAM at 0x20002000: words 0,1 reserved; handlers are absolute addresses.
        String[] names = {"","","NMI_Handler","HardFault_Handler","magic","","","","","","","","SysTick_Handler","","SW_Handler","",
            "TMR0_IRQHandler","GPIOA_IRQHandler","GPIOB_IRQHandler","SPI0_IRQHandler","BB_IRQHandler","LLE_IRQHandler","USB_IRQHandler",
            "USB2_IRQHandler","TMR1_IRQHandler","TMR2_IRQHandler","UART0_IRQHandler","UART1_IRQHandler","RTC_IRQHandler","ADC_IRQHandler",
            "I2C_IRQHandler","PWMX_IRQHandler","TMR3_IRQHandler","UART2_IRQHandler","UART3_IRQHandler","WDOG_BAT_IRQHandler"};
        for (int i = 0; i < names.length; i++) {
            try { lst.createData(toAddr(0x20002000L + 4 * i), PointerDataType.dataType); } catch (Exception ex) { }
            if (names[i].isEmpty() || names[i].equals("magic")) continue;
            long v = mem.getInt(toAddr(0x20002000L + 4 * i)) & 0xFFFFFFFFL;
            if (v == 0) continue;
            String nm = names[i];
            if (v == 0x8ED0L) nm = "Default_Handler_" + i;
            try { st.createLabel(toAddr(v), nm, SourceType.IMPORTED); disassemble(toAddr(v)); createFunction(toAddr(v), null); } catch (Exception ex) { }
        }
        st.createLabel(toAddr(0x1000), "_start", SourceType.USER_DEFINED);
        st.createLabel(toAddr(0x1C48), "handle_reset", SourceType.USER_DEFINED);
        disassemble(toAddr(0x1000)); disassemble(toAddr(0x1C48));
        try { createFunction(toAddr(0x1C48), "handle_reset"); } catch (Exception ex) { }
    }
}
