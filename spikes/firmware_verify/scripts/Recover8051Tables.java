// Recover compiler switch tables and inline constants from reviewed helper code.
// @category MP305
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.data.*;
import java.io.*;
import java.util.*;
public class Recover8051Tables extends GhidraScript{
 int u8(long p)throws Exception{return getByte(toAddr(p))&255;}
 int be16(long p)throws Exception{return (u8(p)<<8)|u8(p+1);}
 public void run()throws Exception{
  try(PrintWriter out=new PrintWriter(getScriptArgs()[0])){
   out.println("call_or_jump\ttable_address\tselector\ttarget\tmethod");
   for(long p=0x1000;p<0xb01b;p++){
    if(u8(p)!=0x12)continue;int helper=be16(p+1);
    if(helper==0xad79 || helper==0xad92){
     disassemble(toAddr(p));Instruction call=getInstructionAt(toAddr(p));
     if(call==null || !call.getMnemonicString().equals("LCALL"))continue;
     clearListing(toAddr(p+3),toAddr(p+6));createData(toAddr(p+3),new ArrayDataType(ByteDataType.dataType,4,1));
     call.setFallThrough(toAddr(p+7));disassemble(toAddr(p+7));
     out.printf("%04x\t%04x\t4_literal_bytes\t%04x\treturn_address_plus_four%n",p,p+3,p+7);
    }
    if(helper!=0xae53)continue;
    List<long[]> rows=new ArrayList<>();long q=p+3;boolean valid=false;
    for(int i=0;i<256 && q+3<0xb022;i++){
     int target=be16(q);
     if(target==0){target=be16(q+2);if(target>=0x1000 && target<0xb022){rows.add(new long[]{q,-1,target});q+=4;valid=true;}break;}
     if(target<0x1000 || target>=0xb022)break;
     rows.add(new long[]{q,u8(q+2),target});q+=3;
    }
    if(!valid)continue;
    disassemble(toAddr(p));Instruction call=getInstructionAt(toAddr(p));if(call==null)continue;
    call.setFallThrough(null);
    clearListing(toAddr(p+3),toAddr(q-1));createData(toAddr(p+3),new ArrayDataType(ByteDataType.dataType,(int)(q-p-3),1));
    for(long[] row:rows){
     currentProgram.getReferenceManager().addMemoryReference(toAddr(p),toAddr(row[2]),RefType.COMPUTED_JUMP,SourceType.USER_DEFINED,-1);
     disassemble(toAddr(row[2]));out.printf("%04x\t%04x\t%s\t%04x\tcompiler_helper_ae53%n",p,row[0],row[1]<0?"default":Long.toString(row[1]),row[2]);
    }
   }
   long[][] tables={{0x25f3,0x25f4,7},{0x5e99,0x5e9a,9},{0xa933,0xa88e,16}};
   for(long[] table:tables)for(int i=0;i<table[2];i++){
    long a=table[1]+2*i;disassemble(toAddr(a));
    currentProgram.getReferenceManager().addMemoryReference(toAddr(table[0]),toAddr(a),RefType.COMPUTED_JUMP,SourceType.USER_DEFINED,-1);
    out.printf("%04x\t%04x\t%d\t%04x\ttwo_byte_jump_slot%n",table[0],table[1],i,a);
   }
  }
  analyzeAll(currentProgram);
 }
}
