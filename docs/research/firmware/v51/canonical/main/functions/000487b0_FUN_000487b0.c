/* Address: 000487b0; name: FUN_000487b0; body bytes: 142 */

int FUN_000487b0(int param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 local_18;
  undefined4 uStack_14;
  
  iVar1 = FUN_0004cd84(param_1,1);
  if (iVar1 == 0) {
    local_18 = *param_2;
    uStack_14 = param_2[1];
    FUN_0004eef4(param_1,&local_18,2);
    iVar1 = FUN_0004cda6(param_1,&local_18);
    local_28 = *(undefined4 *)(param_1 + 0x14);
    uStack_24 = *(undefined4 *)(param_1 + 0x18);
    uStack_20 = *(undefined4 *)(param_1 + 0x1c);
    uStack_1c = *(undefined4 *)(param_1 + 0x20);
    iVar2 = FUN_0004cd84(param_1,0x100000);
    if (iVar2 != 0) {
      uVar3 = FUN_0004bbb0(param_1);
      FUN_0003db32(&local_28,uVar3,uVar3);
    }
    iVar2 = FUN_0003dcb8(&local_28,&local_18,0);
    if (iVar2 != 0) {
      iVar2 = FUN_0004ba5c(param_1);
      while (iVar2 = iVar2 + -1, -1 < iVar2) {
        iVar4 = FUN_000487b0(*(undefined4 *)(**(int **)(param_1 + 8) + iVar2 * 4),&local_18);
        if (iVar4 != 0) {
          return iVar4;
        }
      }
    }
    if (iVar1 != 0) {
      return param_1;
    }
  }
  return 0;
}

