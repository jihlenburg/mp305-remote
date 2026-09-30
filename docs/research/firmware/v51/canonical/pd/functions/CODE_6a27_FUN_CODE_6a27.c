/* Address: CODE:6a27; name: FUN_CODE_6a27; body bytes: 132 */

/* Inferred entry from 9 raw LCALL encodings. Review control flow before relying on semantics. */

void FUN_CODE_6a27(char param_1)

{
  undefined1 uVar1;
  
  DAT_EXTMEM_04a8 = param_1;
  FUN_CODE_626d(0x4c0,param_1);
  FUN_CODE_8bf3(0);
  DAT_EXTMEM_04a9 = 0;
  DAT_EXTMEM_04aa = DAT_EXTMEM_04a8;
  FUN_CODE_87aa(0x57,0xb9,0xff);
  if (DAT_EXTMEM_04a8 == '\x03') {
    uVar1 = 0x5e;
  }
  else if (DAT_EXTMEM_04a8 == '\x04') {
    uVar1 = 0x65;
  }
  else if (DAT_EXTMEM_04a8 == '\x06') {
    uVar1 = 0x6c;
  }
  else {
    uVar1 = 0x73;
    DAT_EXTMEM_04d6 = DAT_EXTMEM_04a9;
    DAT_EXTMEM_04d7 = DAT_EXTMEM_04aa;
  }
  FUN_CODE_87aa(uVar1,0xb9,0xff);
  FUN_CODE_87aa(0x7a,0xb9,0xff);
  if ((DAT_INTMEM_b3 == '\x01') && (DAT_EXTMEM_04a8 == '\x06')) {
    _1_5 = 0;
    FUN_CODE_9436();
  }
  return;
}

