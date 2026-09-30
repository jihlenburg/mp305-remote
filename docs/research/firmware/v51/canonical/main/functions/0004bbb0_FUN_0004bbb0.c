/* Address: 0004bbb0; name: FUN_0004bbb0; body bytes: 10 */

undefined4 FUN_0004bbb0(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (*(int *)(param_1 + 8) != 0) {
    uVar1 = *(undefined4 *)(*(int *)(param_1 + 8) + 0x24);
  }
  return uVar1;
}

