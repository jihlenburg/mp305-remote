/* Address: 0004e0f6; name: FUN_0004e0f6; body bytes: 282 */

void FUN_0004e0f6(int param_1,int param_2,uint param_3)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  
  uVar8 = param_3 & 0xff0000;
  iVar9 = 0xff;
  if (param_2 != 0) {
    if (*(char *)(param_2 + 8) == '\0') {
      iVar9 = 0;
    }
    if ((uVar8 == 0) && (iVar2 = FUN_0006078c(param_2,0x20), iVar2 != 0)) {
      FUN_0004d3d8(param_1);
    }
  }
  uVar7 = 0;
  bVar1 = false;
  while (uVar7 < (*(ushort *)(param_1 + 0x2a) & 0x3ff) >> 4) {
    iVar2 = uVar7 * 8 + 4;
    uVar3 = *(uint *)(*(int *)(param_1 + 0xc) + iVar2);
    if (((((param_3 & 0xffff) == 0xffff) || ((uVar3 & 0xffff) == (param_3 & 0xffff))) &&
        ((uVar8 == 0xf0000 || ((uVar3 & 0xff0000) == uVar8)))) &&
       ((param_2 == 0 || (*(int *)(*(int *)(param_1 + 0xc) + uVar7 * 8) == param_2)))) {
      if ((int)(uVar3 << 6) < 0) {
        FUN_000637cc(param_1,uVar8,0xff,0);
      }
      iVar2 = *(int *)(*(int *)(param_1 + 0xc) + iVar2);
      uVar3 = uVar7;
      if ((iVar2 << 7 < 0) || (iVar2 << 6 < 0)) {
        if (*(int *)(*(int *)(param_1 + 0xc) + uVar7 * 8) != 0) {
          FUN_00050cca();
        }
        FUN_00046bec(*(undefined4 *)(*(int *)(param_1 + 0xc) + uVar7 * 8));
        *(undefined4 *)(*(int *)(param_1 + 0xc) + uVar7 * 8) = 0;
      }
      for (; uVar3 < ((*(ushort *)(param_1 + 0x2a) & 0x3ff) >> 4) - 1; uVar3 = uVar3 + 1) {
        puVar6 = (undefined4 *)(*(int *)(param_1 + 0xc) + uVar3 * 8);
        puVar5 = (undefined4 *)(*(int *)(param_1 + 0xc) + uVar3 * 8 + 8);
        uVar4 = puVar5[1];
        *puVar6 = *puVar5;
        puVar6[1] = uVar4;
      }
      uVar3 = (*(ushort *)(param_1 + 0x2a) >> 4) - 1 & 0x3f;
      *(ushort *)(param_1 + 0x2a) = *(ushort *)(param_1 + 0x2a) & 0xfc0f | (ushort)(uVar3 << 4);
      uVar4 = FUN_0004f588(*(undefined4 *)(param_1 + 0xc),uVar3 << 3);
      bVar1 = true;
      *(undefined4 *)(param_1 + 0xc) = uVar4;
    }
    else {
      uVar7 = uVar7 + 1;
    }
  }
  if ((bVar1) && (iVar9 != 0)) {
    FUN_0004dedc(param_1,uVar8,iVar9);
    return;
  }
  return;
}

