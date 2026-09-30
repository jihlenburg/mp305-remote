/* Address: CODE:7ce1; name: FUN_CODE_7ce1; body bytes: 68 */

void FUN_CODE_7ce1(undefined1 *param_1,char param_2)

{
  byte bVar1;
  
  FUN_CODE_33d6();
  bVar1 = FUN_CODE_33ef();
  if ((bVar1 >> 6 & 1) != 1) {
    return;
  }
  FUN_CODE_9a23(0,2);
  FUN_CODE_343f(0xb3);
  *param_1 = 0;
  FUN_CODE_9c1b();
  FUN_CODE_33f5(DAT_INTMEM_b3 + -0x74,DAT_INTMEM_b3);
  *param_1 = 0;
  FUN_CODE_33d6();
  bVar1 = FUN_CODE_33e2(param_2 + 'Y');
  FUN_CODE_33d3(bVar1 & 0x3f);
  bVar1 = FUN_CODE_33df();
  bVar1 = FUN_CODE_3439(bVar1 & 0xdf);
  FUN_CODE_a99c(bVar1 | 9);
  return;
}

