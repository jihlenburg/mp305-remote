/* Address: 0006320c; name: FUN_0006320c; body bytes: 176 */

void FUN_0006320c(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  undefined1 uVar11;
  int local_28;
  int iStack_24;
  
  local_28 = param_3;
  iStack_24 = param_4;
  iVar1 = FUN_00046688();
  iVar2 = FUN_00046698(param_1);
  if ((iVar1 == 0xb) && ((iVar1 = FUN_00047eec(), iVar1 == 0 || (*(char *)(iVar1 + 8) != '\x01'))))
  {
    iVar1 = FUN_0004bb1a(iVar2);
    iVar3 = FUN_0004baf8(iVar2);
    FUN_0004bd50(iVar2,&local_28);
    iVar4 = local_28 + iVar1 / 2;
    iVar5 = iStack_24 + iVar3 / 2;
    uVar11 = 0xf;
    for (uVar10 = 0; uVar9 = FUN_0004ba5c(iVar2), uVar10 < uVar9; uVar10 = uVar10 + 1) {
      iVar6 = FUN_0004b9de(iVar2,uVar10);
      iVar7 = FUN_0004cd1e();
      iVar8 = FUN_0004cd44(iVar6);
      if ((iVar7 == iVar1 * (iVar4 / iVar1)) && (iVar8 == (iVar5 / iVar3) * iVar3)) {
        *(int *)(iVar2 + 0x2c) = iVar6;
        uVar11 = *(undefined1 *)(iVar6 + 0x2c);
        FUN_0004e5a6(iVar2,0x20,0);
        break;
      }
    }
    FUN_0004e7d8(iVar2,uVar11);
  }
  return;
}

