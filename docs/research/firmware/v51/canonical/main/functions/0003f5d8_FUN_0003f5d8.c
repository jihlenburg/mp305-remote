/* Address: 0003f5d8; name: FUN_0003f5d8; body bytes: 110 */

void FUN_0003f5d8(undefined4 param_1,int param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  while (*(int *)(param_2 + 0x30) != 0) {
    puVar1 = (undefined4 *)FUN_0004a118(param_2 + 0x2c);
    if (puVar1 != (undefined4 *)0x0) {
      if (-1 < (int)((uint)*(byte *)(puVar1 + 4) << 0x1d)) {
        FUN_00046bec(puVar1[1]);
      }
      if (-1 < (int)((uint)*(byte *)(puVar1 + 4) << 0x1e)) {
        FUN_00046bec(*puVar1);
      }
      FUN_0004a2ac(param_2 + 0x2c,puVar1);
      FUN_00046bec(puVar1);
    }
  }
  FUN_0004a0d8();
  while (*(int *)(param_2 + 0x3c) != 0) {
    uVar2 = FUN_0004a118(param_2 + 0x38);
    FUN_0004a2ac(param_2 + 0x38,uVar2);
    FUN_00046bec(uVar2);
  }
  FUN_0004a0d8();
  return;
}

