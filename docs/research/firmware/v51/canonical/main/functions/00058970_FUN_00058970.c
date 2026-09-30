/* Address: 00058970; name: FUN_00058970; body bytes: 242 */

int FUN_00058970(undefined4 *param_1,byte *param_2,byte *param_3,undefined4 param_4)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  byte *pbVar8;
  undefined4 uVar9;
  int iVar10;
  undefined4 *puVar11;
  byte *pbVar12;
  byte *pbVar13;
  undefined4 local_24;
  
  iVar10 = 0;
  puVar11 = param_1;
  pbVar12 = param_2;
  pbVar13 = param_3;
  local_24 = param_4;
  for (; bVar1 = *param_2, bVar1 != 0; param_2 = param_2 + 1) {
    if (bVar1 == 0x25) {
      puVar6 = (undefined4 *)0x0;
      param_2 = param_2 + 1;
      bVar1 = *param_2;
      pbVar8 = (byte *)0x0;
      if (bVar1 == 0) break;
      if (bVar1 == 0x25) goto LAB_00058a44;
      if (bVar1 != 0x2d) goto LAB_000589a6;
      pbVar8 = (byte *)0x1;
      while( true ) {
        param_2 = param_2 + 1;
LAB_000589a6:
        if (*param_2 != 0x30) break;
        pbVar8 = (byte *)((uint)pbVar8 | 2);
      }
      while( true ) {
        uVar2 = (uint)*param_2;
        if (9 < uVar2 - 0x30) break;
        puVar6 = (undefined4 *)(uVar2 + (int)puVar6 * 10 + -0x30);
        param_2 = param_2 + 1;
      }
      if (*param_2 == 0x73) {
        pcVar4 = *(char **)param_3;
        if (pcVar4 == (char *)0x0) {
          pcVar4 = "(null)";
        }
LAB_000589ea:
        iVar3 = FUN_00058b2e(param_1,pcVar4,puVar6,pbVar8,puVar11,pbVar12,pbVar13);
        puVar6 = puVar11;
        pbVar8 = pbVar12;
LAB_00058a0c:
        param_3 = param_3 + 4;
        iVar10 = iVar10 + iVar3;
        puVar11 = puVar6;
        pbVar12 = pbVar8;
      }
      else {
        if (uVar2 == 100) {
          uVar5 = *(undefined4 *)param_3;
          uVar9 = 1;
LAB_00058a30:
          pbVar13 = (byte *)0x61;
          uVar7 = 10;
LAB_00058a06:
          iVar3 = FUN_00058a9c(param_1,uVar5,uVar7,uVar9,puVar6,pbVar8,pbVar13);
          goto LAB_00058a0c;
        }
        if (uVar2 == 0x78) {
          pbVar13 = (byte *)0x61;
LAB_00058a1a:
          uVar9 = 0;
          uVar7 = 0x10;
          uVar5 = *(undefined4 *)param_3;
          goto LAB_00058a06;
        }
        if (uVar2 == 0x58) {
          pbVar13 = (byte *)0x41;
          goto LAB_00058a1a;
        }
        if (uVar2 == 0x75) {
          uVar5 = *(undefined4 *)param_3;
          uVar9 = 0;
          goto LAB_00058a30;
        }
        if (uVar2 == 99) {
          local_24._0_2_ = (ushort)*param_3;
          pcVar4 = (char *)&local_24;
          goto LAB_000589ea;
        }
      }
    }
    else {
LAB_00058a44:
      FUN_00058a6c(param_1,bVar1);
      iVar10 = iVar10 + 1;
    }
  }
  if (param_1 != (undefined4 *)0x0) {
    *(undefined1 *)*param_1 = 0;
  }
  return iVar10;
}

