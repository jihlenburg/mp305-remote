/* Address: 000276c0; name: FUN_000276c0; body bytes: 192 */

void FUN_000276c0(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int local_18;
  int local_14;
  
  local_18 = param_3;
  local_14 = param_4;
  uVar1 = FUN_00046698();
  iVar2 = FUN_00046688(param_1);
  iVar3 = FUN_0004bc8c(uVar1);
  if (iVar2 != 0x30) {
    if ((iVar2 == 0xb) && ((iVar2 = FUN_00047eec(), iVar2 == 0 || (*(char *)(iVar2 + 8) != '\x01')))
       ) {
      FUN_0004bd50(uVar1,&local_18);
      if ((*(byte *)(iVar3 + 0x30) & 0xc) == 0) {
        iVar2 = FUN_0004baf8(uVar1);
        iVar2 = (local_14 + iVar2 / 2) / iVar2;
      }
      else {
        iVar2 = FUN_0004bb1a();
        iVar4 = FUN_0004c5e2(iVar3,0);
        iVar5 = local_18;
        if (iVar4 == 1) {
          iVar5 = -local_18;
        }
        iVar2 = (iVar5 + iVar2 / 2) / iVar2;
      }
      if (iVar2 < 0) {
        iVar2 = 0;
      }
      iVar5 = *(int *)(iVar3 + 0x2c);
      iVar4 = FUN_00047eec();
      FUN_0005152c(iVar3,iVar2,iVar4 != 0);
      if (iVar5 != iVar2) {
        FUN_0004e5a6(iVar3,0x20,0);
      }
    }
    return;
  }
  FUN_0005152c(iVar3,*(undefined4 *)(iVar3 + 0x2c),0);
  return;
}

