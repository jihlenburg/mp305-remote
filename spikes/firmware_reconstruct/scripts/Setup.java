// Ghidra pre-script: HC32F4A0 memory map, SVD register labels, RAM init image, vectors.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.*;
import java.io.*;
import java.nio.file.*;
import java.util.*;

public class Setup extends GhidraScript {
    static final String RE = System.getProperty("user.home") + "/mp305b-fw-re/";

    Address a(long v) { return toAddr(v); }

    MemoryBlock uninit(String name, long start, long len, boolean vol) throws Exception {
        MemoryBlock b = currentProgram.getMemory().createUninitializedBlock(name, a(start), len, false);
        b.setRead(true); b.setWrite(true); b.setExecute(false); b.setVolatile(vol);
        return b;
    }

    public void run() throws Exception {
        Memory mem = currentProgram.getMemory();
        SymbolTable st = currentProgram.getSymbolTable();
        Listing lst = currentProgram.getListing();
        for (MemoryBlock fb : mem.getBlocks()) { fb.setWrite(false); fb.setExecute(true); fb.setName("FLASH_APP"); }
        // Bootloader area, not in the image.
        uninit("BOOT", 0x0, 0x10000, false);
        // RAM: RW init (decompressed by __scatterload) + ZI + rest of SRAM1-3, RetSRAM.
        byte[] rw = Files.readAllBytes(Paths.get(RE + "bin/ram_rw_init.bin"));
        MemoryBlock r = mem.createInitializedBlock("RAM_RW", a(0x1FFE0000L), new ByteArrayInputStream(rw), rw.length, monitor, false);
        r.setRead(true); r.setWrite(true); r.setExecute(false);
        uninit("RAM_ZI", 0x1FFE0000L + rw.length, 0x20060000L - (0x1FFE0000L + rw.length), false);
        uninit("RETRAM", 0x200F0000L, 0x1000, false);
        // Peripherals: merge SVD blocks into non-overlapping ranges.
        TreeMap<Long, Long> rng = new TreeMap<>();
        for (String line : Files.readAllLines(Paths.get(RE + "out/hc32f4a0_periph.txt"))) {
            String[] f = line.trim().split(" ");
            long base = Long.parseLong(f[0], 16), size = Long.parseLong(f[1], 16);
            if (base >= 0xE0000000L || base < 0x40000000L) continue;
            rng.merge(base, base + size, Math::max);
        }
        long cs = -1, ce = -1; int n = 0;
        List<long[]> merged = new ArrayList<>();
        for (Map.Entry<Long, Long> e : rng.entrySet()) {
            if (cs < 0) { cs = e.getKey(); ce = e.getValue(); continue; }
            if (e.getKey() <= ce + 0x400) { ce = Math.max(ce, e.getValue()); }
            else { merged.add(new long[]{cs, ce}); cs = e.getKey(); ce = e.getValue(); }
        }
        merged.add(new long[]{cs, ce});
        for (long[] m : merged) uninit(String.format("PERIPH_%08X", m[0]), m[0], m[1] - m[0], true);
        uninit("SCS", 0xE000E000L, 0x1000, true);
        uninit("DBGC", 0xE0042000L, 0x100, true);
        for (String line : Files.readAllLines(Paths.get(RE + "out/hc32f4a0_periph.txt"))) {
            String[] f = line.trim().split(" ");
            Address ad = a(Long.parseLong(f[0], 16));
            if (Long.parseLong(f[0], 16) < 0x40000000L) continue;
            if (mem.contains(ad)) st.createLabel(ad, f[2], SourceType.IMPORTED);
        }
        for (String line : Files.readAllLines(Paths.get(RE + "out/hc32f4a0_regs.txt"))) {
            String[] f = line.trim().split(" ");
            Address ad = a(Long.parseLong(f[0], 16));
            if (!mem.contains(ad) || Long.parseLong(f[0], 16) < 0x40000000L) continue;
            st.createLabel(ad, f[2], SourceType.IMPORTED);
            DataType dt = f[1].equals("1") ? ByteDataType.dataType : f[1].equals("2") ? WordDataType.dataType : DWordDataType.dataType;
            try { lst.createData(ad, dt); } catch (Exception ex) { }
        }
        String[][] scs = {{"E000ED00","SCB_CPUID"},{"E000ED04","SCB_ICSR"},{"E000ED08","SCB_VTOR"},{"E000ED0C","SCB_AIRCR"},
            {"E000ED10","SCB_SCR"},{"E000ED14","SCB_CCR"},{"E000ED18","SCB_SHPR1"},{"E000ED1C","SCB_SHPR2"},{"E000ED20","SCB_SHPR3"},
            {"E000ED24","SCB_SHCSR"},{"E000ED88","SCB_CPACR"},{"E000EF34","FPU_FPCCR"},{"E000E010","SysTick_CTRL"},
            {"E000E014","SysTick_LOAD"},{"E000E018","SysTick_VAL"},{"E000E100","NVIC_ISER"},{"E000E180","NVIC_ICER"},
            {"E000E200","NVIC_ISPR"},{"E000E280","NVIC_ICPR"},{"E000E400","NVIC_IPR"},{"E000EF00","NVIC_STIR"},{"E000EDF0","CoreDebug_DHCSR"}};
        for (String[] s : scs) st.createLabel(a(Long.parseLong(s[0], 16)), s[1], SourceType.IMPORTED);
        // Vector table at 0x10000: 16 system + 144 IRQ.
        String[] sys = {"__initial_sp","Reset_Handler","NMI_Handler","HardFault_Handler","MemManage_Handler","BusFault_Handler",
            "UsageFault_Handler","","","","","SVC_Handler","DebugMon_Handler","","PendSV_Handler","SysTick_Handler"};
        for (int i = 0; i < 160; i++) {
            Address va = a(0x10000 + 4 * i);
            try { lst.createData(va, PointerDataType.dataType); } catch (Exception ex) { }
            long v = mem.getInt(va) & 0xFFFFFFFFL;
            String nm = i < 16 ? sys[i] : String.format("IRQ%03d_Handler", i - 16);
            if (i == 0 || nm.isEmpty() || v == 0 || v == 0xFFFFFFFFL) continue;
            if (v < 0x10000 || v >= 0x84400) continue;
            Address fa = a(v & ~1L);
            st.createLabel(fa, nm, SourceType.IMPORTED);
            disassemble(fa);
            try { createFunction(fa, null); } catch (Exception ex) { }
        }
        // Scatter table and init functions known from the startup walk.
        st.createLabel(a(0x10281), "__main_thumb", SourceType.USER_DEFINED);
        for (long[] f : new long[][]{{0x10280},{0x10ee4},{0x11652},{0x202cc},{0x1DB74},{0x533C0}}) {
            disassemble(a(f[0])); try { createFunction(a(f[0]), null); } catch (Exception ex) { }
        }
        st.createLabel(a(0x10280), "__main", SourceType.USER_DEFINED);
        st.createLabel(a(0x10ee4), "__scatterload", SourceType.USER_DEFINED);
        st.createLabel(a(0x11652), "__decompress", SourceType.USER_DEFINED);
        st.createLabel(a(0x202cc), "__scatterload_zeroinit", SourceType.USER_DEFINED);
        st.createLabel(a(0x1DB74), "SystemInit", SourceType.USER_DEFINED);
        st.createLabel(a(0x533C0), "main", SourceType.USER_DEFINED);
        setAnalysisOption(currentProgram, "ARM Aggressive Instruction Finder", "true");
        setAnalysisOption(currentProgram, "Decompiler Parameter ID", "true");
    }
}
