/* Address: 00048de4; name: FUN_00048de4; body bytes: 288 */

void FUN_00048de4(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  int *piVar8;
  
  uVar4 = param_2;
  iVar2 = FUN_0004b9b2(&PTR_DAT_0007aadc);
  if (iVar2 == 1) {
    iVar2 = FUN_00046688(param_2);
    iVar3 = FUN_00046698(param_2);
    if ((iVar2 == 0x2f) || (iVar2 == 0x2e)) {
      FUN_00049898();
      FUN_000493d0(iVar3,uVar4,param_3,param_4);
      return;
    }
    if (iVar2 == 0x18) {
      FUN_0004cb34(iVar3,0);
      iVar2 = FUN_00046bd6();
      FUN_00046862(param_2,(int)(iVar2 + ((uint)(iVar2 >> 0x1f) >> 0x1e)) >> 2);
      return;
    }
    if (iVar2 == 0x31) {
      if ((int)((uint)*(byte *)(iVar3 + 0x5c) << 0x19) < 0) {
        uVar4 = FUN_0004cb34(iVar3,0);
        uVar5 = FUN_0004cb58(iVar3,0);
        uVar6 = FUN_0004cb7c(iVar3,0);
        bVar1 = *(byte *)(iVar3 + 0x5c);
        FUN_0004bb1a(iVar3);
        iVar2 = FUN_0004cbea(iVar3,0);
        if ((iVar2 == 0x3fffffff) && (-1 < (int)((uint)*(ushort *)(iVar3 + 0x2a) << 0x14))) {
          iVar2 = 0x1fffffff;
        }
        else {
          iVar2 = FUN_0004bb1a(iVar3);
        }
        iVar7 = FUN_0004c75c(iVar3,0);
        if (iVar7 <= iVar2) {
          iVar2 = FUN_0004c75c(iVar3,0);
        }
        FUN_00051970(iVar3 + 0x4c,*(undefined4 *)(iVar3 + 0x2c),uVar4,uVar5,uVar6,iVar2,
                     (int)((uint)bVar1 << 0x1b) < 0);
        *(byte *)(iVar3 + 0x5c) = *(byte *)(iVar3 + 0x5c) & 0xbf;
      }
      piVar8 = (int *)FUN_0004673a(param_2);
      iVar2 = *(int *)(iVar3 + 0x4c);
      if (*(int *)(iVar3 + 0x4c) < *piVar8) {
        iVar2 = *piVar8;
      }
      *piVar8 = iVar2;
      iVar2 = piVar8[1];
      if (piVar8[1] <= *(int *)(iVar3 + 0x50)) {
        iVar2 = *(int *)(iVar3 + 0x50);
      }
      piVar8[1] = iVar2;
    }
    else if (iVar2 == 0x1a) {
      FUN_0002d842(param_2,uVar4,param_3,param_4);
      return;
    }
  }
  return;
}

