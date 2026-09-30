// Index every decoded memory access and add decompiler-based address expressions.
// Raw instruction records remain separate from heuristic high-pcode records.
// @category MP305
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.pcode.*;
import ghidra.program.model.address.*;
import ghidra.program.model.mem.*;
import java.io.*;
import java.util.*;
public class ExportMemoryAccesses extends GhidraScript {
  String clean(String s) { return s.replace('\t',' ').replace('\n',' '); }
  Long value(Varnode v,int depth,Set<Varnode> seen) {
    if(v==null || depth<0 || !seen.add(v))return null;
    if(v.isConstant())return v.getOffset();
    // Only read immutable mapped firmware bytes, never mutable initial RAM.
    if(v.getAddress().isMemoryAddress()) {
      MemoryBlock b=currentProgram.getMemory().getBlock(v.getAddress());
      if(b!=null && b.isInitialized() && !b.isWrite() && v.getSize()<=8) {
        try { byte[] bytes=new byte[v.getSize()];currentProgram.getMemory().getBytes(v.getAddress(),bytes);
          long n=0;for(int i=0;i<bytes.length;i++){int j=currentProgram.getLanguage().isBigEndian()?i:bytes.length-1-i;n=(n<<8)|(bytes[j]&255);}return n;
        } catch(Exception e) { return null; }
      }
    }
    PcodeOp p=v.getDef(); if(p==null)return null;
    int op=p.getOpcode();
    Long a=p.getNumInputs()>0?value(p.getInput(0),depth-1,new HashSet<>(seen)):null;
    Long b=p.getNumInputs()>1?value(p.getInput(1),depth-1,new HashSet<>(seen)):null;
    Long c=p.getNumInputs()>2?value(p.getInput(2),depth-1,new HashSet<>(seen)):null;
    Long r=null;
    switch(op) {
      case PcodeOp.COPY: case PcodeOp.CAST: case PcodeOp.INT_ZEXT: r=a;break;
      case PcodeOp.INT_ADD: case PcodeOp.PTRSUB: if(a!=null&&b!=null)r=a+b;break;
      case PcodeOp.INT_SUB: if(a!=null&&b!=null)r=a-b;break;
      case PcodeOp.INT_MULT: if(a!=null&&b!=null)r=a*b;break;
      case PcodeOp.INT_LEFT: if(a!=null&&b!=null)r=a<<b;break;
      case PcodeOp.INT_RIGHT: if(a!=null&&b!=null)r=a>>>b;break;
      case PcodeOp.INT_AND: if(a!=null&&b!=null)r=a&b;break;
      case PcodeOp.INT_OR: if(a!=null&&b!=null)r=a|b;break;
      case PcodeOp.PTRADD: if(a!=null&&b!=null&&c!=null)r=a+b*c;break;
      case PcodeOp.MULTIEQUAL:
        r=a;for(int i=1;i<p.getNumInputs();i++){Long x=value(p.getInput(i),depth-1,new HashSet<>(seen));if(!Objects.equals(r,x)){r=null;break;}}break;
    }
    if(r!=null&&v.getSize()<8)r &= (1L<<(v.getSize()*8))-1;
    return r;
  }
  String expr(Varnode v,int depth) {
    if(v==null)return "";
    Long n=value(v,depth,new HashSet<>());if(n!=null)return "0x"+Long.toHexString(n);
    if(v.getAddress().isMemoryAddress())return "mem["+v.getAddress()+"]";
    PcodeOp p=v.getDef();if(depth<1||p==null)return v.toString();
    StringBuilder b=new StringBuilder(p.getMnemonic()+"(");
    for(int i=0;i<p.getNumInputs();i++){if(i>0)b.append(',');String part=expr(p.getInput(i),depth-1);b.append(part);if(b.length()>512){b.setLength(512);b.append("...[truncated]");break;}}return b.append(')').toString();
  }
  void row(PrintWriter w,String phase,String fn,Address at,String ins,int ordinal,String rw,String space,int size,String expression,String resolved,String data) {
    w.printf("%s\t%s\t%s\t%s\t%d\t%s\t%s\t%d\t%s\t%s\t%s%n",phase,fn,at,clean(ins),ordinal,rw,space,size,clean(expression),resolved,clean(data));
  }
  void emit(PrintWriter w,String phase,String fn,Address at,String ins,int ordinal,PcodeOp p) {
    int op=p.getOpcode();
    // SSA bookkeeping operations do not represent additional bus accesses.
    if(op==PcodeOp.INDIRECT||op==PcodeOp.MULTIEQUAL)return;
    if(op==PcodeOp.LOAD||op==PcodeOp.STORE) {
      Varnode ptr=p.getInput(1); Long a=value(ptr,10,new HashSet<>());
      AddressSpace sp=currentProgram.getAddressFactory().getAddressSpace((int)p.getInput(0).getOffset());
      String name=sp==null?"unknown":sp.getName();
      row(w,phase,fn,at,ins,ordinal,op==PcodeOp.LOAD?"read":"write",name,op==PcodeOp.LOAD?p.getOutput().getSize():p.getInput(2).getSize(),expr(ptr,7),a==null?"":"0x"+Long.toHexString(a),op==PcodeOp.STORE?expr(p.getInput(2),5):"");
    }
    Varnode out=p.getOutput();
    if(out!=null&&out.getAddress().isMemoryAddress())row(w,phase,fn,at,ins,ordinal,"write",out.getAddress().getAddressSpace().getName(),out.getSize(),out.getAddress().toString(),"0x"+Long.toHexString(out.getOffset()),expr(p.getInput(0),5));
    for(int j=0;j<p.getNumInputs();j++) {
      Varnode in=p.getInput(j);
      if(in.getAddress().isMemoryAddress()&&op!=PcodeOp.CALL&&op!=PcodeOp.BRANCH&&op!=PcodeOp.CBRANCH)
        row(w,phase,fn,at,ins,ordinal,"read",in.getAddress().getAddressSpace().getName(),in.getSize(),in.getAddress().toString(),"0x"+Long.toHexString(in.getOffset()),"");
    }
  }
  public void run() throws Exception {
    File dir=new File(getScriptArgs()[0]);dir.mkdirs();
    try(PrintWriter raw=new PrintWriter(new File(dir,"memory-accesses-raw.tsv"));PrintWriter high=new PrintWriter(new File(dir,"memory-accesses-high.tsv"));PrintWriter status=new PrintWriter(new File(dir,"memory-accesses-status.tsv"))) {
      String header="phase\tfunction\tinstruction\tdisassembly\top_index\tdirection\tspace\tbytes\taddress_expression\tresolved_address\tvalue_expression";raw.println(header);high.println(header);status.println("function\tdecompiled\terror");
      for(Instruction i:currentProgram.getListing().getInstructions(true)) {
        Function f=currentProgram.getFunctionManager().getFunctionContaining(i.getAddress());int n=0;
        for(PcodeOp p:i.getPcode())emit(raw,"instruction",f==null?"unassigned":f.getEntryPoint().toString(),i.getAddress(),i.toString(),n++,p);
      }
      DecompInterface d=new DecompInterface();d.openProgram(currentProgram);int count=0;
      for(Function f:currentProgram.getFunctionManager().getFunctions(true)) {
        if(monitor.isCancelled())break;
        DecompileResults r=d.decompileFunction(f,45,monitor);status.printf("%s\t%s\t%s%n",f.getEntryPoint(),r.decompileCompleted(),clean(r.getErrorMessage()));
        if(r.getHighFunction()!=null) {
          Iterator<PcodeOpAST> ops=r.getHighFunction().getPcodeOps();
          while(ops.hasNext()){PcodeOpAST p=ops.next();Address at=p.getSeqnum().getTarget();Instruction i=getInstructionAt(at);if(i!=null) {
              boolean memory=false;
              for(PcodeOp rawop:i.getPcode()) {
                if(rawop.getOpcode()==PcodeOp.LOAD||rawop.getOpcode()==PcodeOp.STORE)memory=true;
                if(rawop.getOutput()!=null&&rawop.getOutput().getAddress().isMemoryAddress())memory=true;
                for(Varnode v:rawop.getInputs())if(v.getAddress().isMemoryAddress())memory=true;
              }
              if(memory)emit(high,"decompiler",f.getEntryPoint().toString(),at,i.toString(),p.getSeqnum().getTime(),p);
            }}
        }
        if(++count%300==0)println("Memory index: "+count+" functions");
      }
      d.dispose();println("Memory access export complete");
    }
  }
}
