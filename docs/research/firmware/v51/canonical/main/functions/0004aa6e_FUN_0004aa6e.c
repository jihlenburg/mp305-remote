/* Address: 0004aa6e; name: FUN_0004aa6e; body bytes: 136 */

void FUN_0004aa6e(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  undefined1 auStack_38 [16];
  undefined1 auStack_28 [20];
  
  iVar1 = FUN_0004d498();
  if ((param_2 & 1) != 0) {
    FUN_0004d3d8(param_1);
  }
  *(uint *)(param_1 + 0x24) = *(uint *)(param_1 + 0x24) | param_2;
  if ((((param_2 & 1) != 0) && (iVar2 = FUN_0004cd9c(param_1,2), iVar2 != 0)) &&
     (iVar2 = FUN_0004bbe2(param_1), iVar2 != 0)) {
    FUN_000471d8();
    iVar2 = FUN_000472e0(iVar2);
    if (iVar2 != 0) {
      FUN_0004d3d8();
    }
  }
  iVar2 = FUN_0004d498(param_1);
  if ((iVar2 != iVar1) || ((param_2 & 0x1800000) != 0)) {
    FUN_0004bc8c(param_1);
    FUN_0004d500();
    FUN_0004d500(param_1);
  }
  if ((int)(param_2 << 0x1b) < 0) {
    FUN_0004bf38(param_1,auStack_38,auStack_28);
    FUN_0004d40e(param_1,auStack_38);
    FUN_0004d40e(param_1,auStack_28);
  }
  return;
}

