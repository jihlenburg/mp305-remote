/* Address: CODE:6e51; name: FUN_CODE_6e51; body bytes: 107 */

void FUN_CODE_6e51(void)

{
  if (DAT_INTMEM_b4 < 0x11) {
    FUN_CODE_94cc(DAT_INTMEM_b4 - 0x11);
    return;
  }
  if (DAT_INTMEM_b4 < 0x1c) {
    FUN_CODE_4920(DAT_INTMEM_b4 - 0x1c);
    return;
  }
  if (DAT_INTMEM_b4 < 0x3f) {
    FUN_CODE_8f3f(DAT_INTMEM_b4 - 0x3f);
    return;
  }
  if (DAT_INTMEM_b4 < 0x41) {
    FUN_CODE_a775(DAT_INTMEM_b4 + 0xbf);
    return;
  }
  if (DAT_INTMEM_b4 < 0x43) {
    FUN_CODE_a313(DAT_INTMEM_b4 + 0xbd);
    return;
  }
  if (DAT_INTMEM_b4 < 0x49) {
    FUN_CODE_4b5e(DAT_INTMEM_b4 + 0xb7);
    return;
  }
  if (DAT_INTMEM_b4 < 0x4c) {
    FUN_CODE_a6bb(DAT_INTMEM_b4 + 0xb4);
    return;
  }
  if (DAT_INTMEM_b4 < 0x50) {
    FUN_CODE_8e33(DAT_INTMEM_b4 + 0xb0);
    return;
  }
  if ((DAT_INTMEM_b4 != 0x50) && (DAT_INTMEM_b4 == 0x51)) {
    FUN_CODE_a3ef();
    FUN_CODE_101e();
  }
  return;
}

