/* Address: 00010c40; name: FUN_00010c40; body bytes: 30 */

/* Recovered from stored Thumb pointer at 00010580; callback identification is inferred until
   reviewed. */

uint FUN_00010c40(undefined4 *param_1)

{
  uint uVar1;
  
  if (param_1[1] != 0) {
    uVar1 = (uint)*(byte *)*param_1;
    if (uVar1 != 0) {
      *param_1 = (byte *)*param_1 + 1;
      param_1[1] = param_1[1] + -1;
      return uVar1;
    }
  }
  param_1[3] = 1;
  return 0xffffffff;
}

