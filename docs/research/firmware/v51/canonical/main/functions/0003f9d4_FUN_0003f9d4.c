/* Address: 0003f9d4; name: FUN_0003f9d4; body bytes: 114 */

void FUN_0003f9d4(int param_1,int param_2)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x70) != param_2) {
    if (param_2 == 0) {
      param_2 = 1;
    }
    for (iVar1 = FUN_0004a14a(); iVar1 != 0; iVar1 = FUN_0004a144(param_1 + 0x2c,iVar1)) {
      if (((*(byte *)(param_1 + 0x74) & 7) == 3) &&
         (-1 < (int)((uint)*(byte *)(iVar1 + 0x10) << 0x1e))) {
        FUN_00053fb8(param_1,iVar1,param_2);
      }
      if (-1 < (int)((uint)*(byte *)(iVar1 + 0x10) << 0x1d)) {
        FUN_00053fb8(param_1,iVar1,param_2,iVar1 + 4);
      }
      *(undefined4 *)(iVar1 + 0xc) = 0;
    }
    *(int *)(param_1 + 0x70) = param_2;
    FUN_0004d3d8(param_1);
    return;
  }
  return;
}

