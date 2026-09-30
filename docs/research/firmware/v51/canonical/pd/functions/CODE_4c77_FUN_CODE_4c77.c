/* Address: CODE:4c77; name: FUN_CODE_4c77; body bytes: 75 */

void FUN_CODE_4c77(byte param_1,undefined1 param_2,undefined1 param_3)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  
  DAT_EXTMEM_04bc = param_2;
  DAT_EXTMEM_04bd = param_3;
  FUN_CODE_ae2a(0x4b9);
  FUN_CODE_aac4(2);
  param_1 = param_1 >> 2;
  bVar2 = 0;
  bVar4 = FUN_CODE_aa99();
  bVar3 = 0;
  cVar1 = '\x06';
  bVar4 = bVar4 & 0xf;
  do {
    bVar5 = bVar4 << 1;
    bVar3 = bVar3 << 1 | bVar4 >> 7;
    cVar1 = cVar1 + -1;
    bVar4 = bVar5;
  } while (cVar1 != '\0');
  bVar3 = bVar3 | bVar2;
  bVar5 = bVar5 | param_1;
  FUN_CODE_aed0(0,0x32);
  DAT_EXTMEM_04c0 = bVar3;
  DAT_EXTMEM_04c1 = bVar5;
                    /* WARNING: Subroutine does not return */
  FUN_CODE_adf3(0x4b9);
}

