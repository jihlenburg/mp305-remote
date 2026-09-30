/* Address: CODE:7c57; name: FUN_CODE_7c57; body bytes: 69 */

void FUN_CODE_7c57(void)

{
  byte bVar1;
  char in_PSW;
  
  FUN_CODE_50c8();
  FUN_CODE_a335();
  if (-1 < in_PSW) {
    bVar1 = DAT_INTMEM_cb & 0x70;
    if (bVar1 == 0x20) {
      DAT_EXTMEM_04ae = 5;
      DAT_EXTMEM_04af = 0xdc;
      goto LAB_CODE_7c8d;
    }
    if (bVar1 != 0x40) {
      if (bVar1 == 0x10) {
        FUN_CODE_50c8();
      }
      goto LAB_CODE_7c8d;
    }
  }
  DAT_EXTMEM_04ae = 0xb;
  DAT_EXTMEM_04af = 0xb8;
LAB_CODE_7c8d:
  thunk_FUN_CODE_8832(DAT_EXTMEM_04ae,DAT_EXTMEM_04af,0x13,0x88);
  return;
}

