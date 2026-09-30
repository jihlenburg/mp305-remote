/* Address: 00010d1c; name: FUN_00010d1c; body bytes: 112 */

int FUN_00010d1c(byte *param_1,undefined4 *param_2,undefined4 param_3)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  byte *pbVar4;
  byte *pbVar6;
  uint uVar7;
  int iVar8;
  bool bVar9;
  byte *pbVar5;
  
  iVar8 = 0;
  pbVar4 = param_1;
  do {
    pbVar5 = pbVar4;
    pbVar4 = pbVar5 + 1;
    uVar7 = (uint)*pbVar5;
    if (uVar7 == 0) break;
    piVar1 = (int *)FUN_00010f08();
  } while ((*(byte *)(*piVar1 + uVar7) & 1) != 0);
  pbVar6 = pbVar4;
  if ((uVar7 != 0x2b) && (pbVar6 = pbVar5, uVar7 == 0x2d)) {
    iVar8 = 0x400;
    pbVar6 = pbVar4;
  }
  iVar2 = FUN_000115b4(pbVar6,param_2,param_3);
  if ((param_2 != (undefined4 *)0x0) && ((byte *)*param_2 == pbVar6)) {
    *param_2 = param_1;
  }
  if (iVar8 << 0x15 < 0) {
    iVar8 = -iVar2;
    bVar9 = iVar2 != 0;
    iVar2 = iVar8;
    if (bVar9 && -1 < iVar8) {
      puVar3 = (undefined4 *)FUN_00020158();
      *puVar3 = 2;
      iVar2 = -0x80000000;
    }
  }
  else if (iVar2 < 0) {
    puVar3 = (undefined4 *)FUN_00020158();
    *puVar3 = 2;
    iVar2 = 0x7fffffff;
  }
  return iVar2;
}

