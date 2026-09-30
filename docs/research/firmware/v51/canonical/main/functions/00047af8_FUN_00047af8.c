/* Address: 00047af8; name: FUN_00047af8; body bytes: 28 */

void FUN_00047af8(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = FUN_0004f098(*(undefined4 *)(param_1 + 0x50),*(undefined4 *)(param_1 + 0x3c));
  *param_2 = uVar1;
  uVar1 = FUN_0004f098(*(undefined4 *)(param_1 + 0x54),*(undefined4 *)(param_1 + 0x40));
  param_2[1] = uVar1;
  return;
}

