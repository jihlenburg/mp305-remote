/* Address: 00049ad4; name: FUN_00049ad4; body bytes: 32 */

/* Recovered from stored Thumb pointer at 0007ab04; callback identification is inferred until
   reviewed. */

void FUN_00049ad4(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  undefined2 local_10;
  undefined1 uStack_e;
  
  uVar1 = FUN_000526c4(param_2);
  local_10 = (undefined2)uVar1;
  *(undefined2 *)(param_2 + 0x2c) = local_10;
  uStack_e = (undefined1)((uint)uVar1 >> 0x10);
  *(undefined1 *)(param_2 + 0x2e) = uStack_e;
  *(undefined1 *)(param_2 + 0x2f) = 0xff;
  return;
}

