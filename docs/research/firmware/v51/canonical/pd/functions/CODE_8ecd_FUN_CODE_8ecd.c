/* Address: CODE:8ecd; name: FUN_CODE_8ecd; body bytes: 38 */

void FUN_CODE_8ecd(byte param_1)

{
  undefined1 uVar1;
  
  DAT_EXTMEM_04ac = param_1;
  if ((param_1 >> 1 & 1) != 0) {
    DAT_EXTMEM_04ac = 2;
  }
  FUN_CODE_a6df(DAT_EXTMEM_04ac);
  uVar1 = (&DAT_CODE_b902)[DAT_EXTMEM_04ac];
  FUN_CODE_33d6(uVar1);
  FUN_CODE_a9ae(uVar1,0x61);
  return;
}

