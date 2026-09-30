/* Address: 00052b38; name: FUN_00052b38; body bytes: 16 */

uint FUN_00052b38(int param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  if (param_1 != 0) {
    uVar1 = *(uint *)(param_1 + -4) & 0xfffffffc;
  }
  return uVar1;
}

