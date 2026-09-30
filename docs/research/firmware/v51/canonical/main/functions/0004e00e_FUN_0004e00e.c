/* Address: 0004e00e; name: FUN_0004e00e; body bytes: 120 */

void FUN_0004e00e(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  
  iVar1 = FUN_0004d498();
  if ((int)(param_2 << 0x1b) < 0) {
    FUN_0004bf38(param_1,auStack_30,auStack_20);
    FUN_0004d40e(param_1,auStack_30);
    FUN_0004d40e(param_1,auStack_20);
  }
  *(uint *)(param_1 + 0x24) = *(uint *)(param_1 + 0x24) & ~param_2;
  if ((param_2 & 1) != 0) {
    FUN_0004d3d8(param_1);
    iVar2 = FUN_0004d498(param_1);
    if (iVar2 != 0) {
      FUN_0004bc8c(param_1);
      FUN_0004d500();
      FUN_0004d500(param_1);
    }
  }
  iVar2 = FUN_0004d498(param_1);
  if ((iVar2 == iVar1) && ((param_2 & 0x1800000) == 0)) {
    return;
  }
  FUN_0004bc8c(param_1);
  FUN_0004d500();
  return;
}

