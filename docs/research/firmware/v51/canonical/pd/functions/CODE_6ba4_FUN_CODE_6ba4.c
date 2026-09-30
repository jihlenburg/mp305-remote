/* Address: CODE:6ba4; name: FUN_CODE_6ba4; body bytes: 119 */

/* Inferred entry from 3 raw LCALL encodings. Review control flow before relying on semantics. */

void FUN_CODE_6ba4(char param_1,char param_2,byte param_3)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  byte *pbVar4;
  
  pbVar4 = (byte *)CONCAT11(-0x48 - (((200U < (byte)(DAT_INTMEM_cc * '\x02')) << 7) >> 7),
                            DAT_INTMEM_cc * '\x02' + 0x37);
  DAT_EXTMEM_04aa = *pbVar4;
  DAT_EXTMEM_04ab = pbVar4[1];
  DAT_EXTMEM_04a8 = param_2;
  DAT_EXTMEM_04a9 = param_3;
  FUN_CODE_9561(param_2,param_3);
  FUN_CODE_9d73();
  FUN_CODE_ab49(param_2,param_3);
  cVar2 = DAT_EXTMEM_04ab + param_3;
  bVar1 = param_2 - ((CARRY1(DAT_EXTMEM_04ab,param_3) << 7) >> 7);
  cVar3 = CARRY1(DAT_EXTMEM_04aa,bVar1) << 7;
  FUN_CODE_ab68(DAT_EXTMEM_04aa + bVar1,2,cVar2);
  FUN_CODE_4503(0x4aa);
  bVar1 = cVar2 - (cVar3 >> 7);
  FUN_CODE_ab68(param_2 - (param_1 - (((param_3 < bVar1) << 7) >> 7)),4,param_3 - bVar1);
  FUN_CODE_ab68(6,0);
  FUN_CODE_ab68(DAT_EXTMEM_04a8,8,DAT_EXTMEM_04a9);
  return;
}

