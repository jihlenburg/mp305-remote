/* Address: 000440c4; name: FUN_000440c4; body bytes: 224 */

void FUN_000440c4(undefined4 param_1,int param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  
  if (((2 < *(byte *)(param_2 + 0x28)) && (*(int *)(param_2 + 0x24) != 0)) &&
     ((*(byte *)(param_2 + 0x29) & 0x1f) != 0)) {
    iVar1 = FUN_0003db28(param_3);
    iVar2 = FUN_0003db0a(param_3);
    if (iVar2 <= iVar1) {
      iVar1 = iVar2;
    }
    iVar2 = *(int *)(param_2 + 0x1c);
    if (iVar1 >> 1 < *(int *)(param_2 + 0x1c)) {
      iVar2 = iVar1 >> 1;
    }
    local_24 = *(int *)(param_2 + 0x24);
    if (-1 < (int)((uint)*(byte *)(param_2 + 0x29) << 0x1d)) {
      local_24 = -(local_24 + iVar2);
    }
    local_24 = local_24 + *param_3;
    local_1c = *(int *)(param_2 + 0x24);
    if (-1 < (int)((uint)*(byte *)(param_2 + 0x29) << 0x1c)) {
      local_1c = -(local_1c + iVar2);
    }
    local_1c = param_3[2] - local_1c;
    local_20 = *(int *)(param_2 + 0x24);
    if (-1 < (int)((uint)*(byte *)(param_2 + 0x29) << 0x1e)) {
      local_20 = -(local_20 + iVar2);
    }
    local_20 = local_20 + param_3[1];
    local_18 = *(int *)(param_2 + 0x24);
    if ((*(byte *)(param_2 + 0x29) & 1) == 0) {
      local_18 = -(local_18 + iVar2);
    }
    local_18 = param_3[3] - local_18;
    iVar1 = iVar2 - *(int *)(param_2 + 0x24);
    if (iVar1 < 0) {
      iVar1 = 0;
    }
    if (iVar2 == 0 && iVar1 == 0) {
      FUN_0002948c(param_1,param_3,&local_24,*(undefined4 *)(param_2 + 0x20),
                   *(undefined1 *)(param_2 + 0x28));
    }
    else {
      FUN_00029106(param_1,param_3,&local_24,iVar2,iVar1,*(undefined2 *)(param_2 + 0x20),
                   *(undefined1 *)(param_2 + 0x28));
    }
  }
  return;
}

