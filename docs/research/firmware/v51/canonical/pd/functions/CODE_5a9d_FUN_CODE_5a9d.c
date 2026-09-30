/* Address: CODE:5a9d; name: FUN_CODE_5a9d; body bytes: 202 */

/* Inferred entry from 6 raw LCALL encodings. Review control flow before relying on semantics. */

void FUN_CODE_5a9d(byte param_1,char param_2,char param_3,undefined1 param_4)

{
  char cVar1;
  byte bVar2;
  byte in_PSW;
  
  DAT_EXTMEM_04af = 0;
  DAT_EXTMEM_04b0 = 0;
  DAT_EXTMEM_04b1 = 0;
  DAT_EXTMEM_04a8 = param_4;
  DAT_EXTMEM_04a9 = param_3;
  DAT_EXTMEM_04aa = param_2;
  if (param_2 == '\0') {
    if (param_3 == 'c') {
      DAT_EXTMEM_04af = 0x80;
      DAT_EXTMEM_04b0 = 0x87;
    }
  }
  else {
    FUN_CODE_974d(0);
    FUN_CODE_4739();
    DAT_EXTMEM_04b1 = param_1 & 7;
    in_PSW = in_PSW & 0xdd;
    DAT_EXTMEM_04b0 = FUN_CODE_aa99();
    bVar2 = DAT_EXTMEM_04b0;
    if (DAT_EXTMEM_04b0 == 0) {
      bVar2 = ~param_1;
    }
    DAT_EXTMEM_04af = param_1;
    if ((bVar2 != 0) ||
       ((FUN_CODE_a340(1), (char)in_PSW < '\0' && (FUN_CODE_a335(), (char)in_PSW < '\0')))) {
      DAT_EXTMEM_04aa = '\x02';
    }
  }
  DAT_EXTMEM_04b6 = DAT_EXTMEM_04b1;
  cVar1 = DAT_EXTMEM_04a9;
  FUN_CODE_6000(DAT_EXTMEM_04af,DAT_EXTMEM_04b0,DAT_EXTMEM_04aa);
  DAT_EXTMEM_04ae = cVar1;
  FUN_CODE_9d85();
  FUN_CODE_ae2a(0x4ab);
  if (DAT_EXTMEM_04a9 == 'b') {
    if (DAT_EXTMEM_04aa != '\x01') goto LAB_CODE_5b4d;
    FUN_CODE_a7f6();
  }
  else {
    if ((DAT_EXTMEM_04a9 != 'a') || (DAT_EXTMEM_04aa != '\x01')) goto LAB_CODE_5b4d;
    FUN_CODE_72d3();
  }
  DAT_EXTMEM_04ae = DAT_EXTMEM_04ae + cVar1;
LAB_CODE_5b4d:
                    /* WARNING: Subroutine does not return */
  FUN_CODE_adf3(0x4ab,DAT_EXTMEM_04ae * '\x04',DAT_EXTMEM_04a9,DAT_EXTMEM_04ae,DAT_EXTMEM_04a8);
}

