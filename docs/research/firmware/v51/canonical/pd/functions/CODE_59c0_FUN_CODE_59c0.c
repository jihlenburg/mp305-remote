/* Address: CODE:59c0; name: FUN_CODE_59c0; body bytes: 184 */

void FUN_CODE_59c0(void)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  short sVar4;
  
  DAT_EXTMEM_04a4 = '\0';
  DAT_EXTMEM_04a5 = DAT_EXTMEM_055c;
  DAT_EXTMEM_04a6 = 0;
  DAT_EXTMEM_04a7 = DAT_EXTMEM_055d;
  DAT_EXTMEM_05dc = 0;
  DAT_EXTMEM_05dd = 0;
  bVar2 = 0xb9;
  bVar1 = 0x83;
  DAT_EXTMEM_04d6 = 0;
  DAT_EXTMEM_04d7 = DAT_EXTMEM_055c;
  DAT_EXTMEM_04d8 = 0;
  DAT_EXTMEM_04d9 = DAT_EXTMEM_055d;
  DAT_EXTMEM_04da = 0;
  DAT_EXTMEM_04db = DAT_EXTMEM_055e;
  FUN_CODE_87aa(0x83,0xff);
  sVar4 = 0x4a5;
  if (DAT_EXTMEM_04a4 == '\0') {
    bVar3 = FUN_CODE_ae53(DAT_EXTMEM_04a5);
    nop();
    bVar3 = func_0x5cb0((bVar3 & bVar2 | bVar1) & bVar2);
    bVar1 = IPL1;
    IPL1 = bVar1 & 0x5a;
                    /* WARNING: Could not recover jumptable at 0x5a2e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*(code *)(sVar4 + (ushort)(bVar3 & bVar2)))();
    return;
  }
  FUN_CODE_87aa(0x94,0xb9,0xff);
  return;
}

