/* Address: 00037610; name: FUN_00037610; body bytes: 212 */

undefined4 FUN_00037610(int param_1,uint param_2)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  uint uVar6;
  undefined4 *puVar7;
  undefined4 uVar8;
  
  uVar1 = *(ushort *)(param_1 + 0x2a);
  for (uVar2 = 0; uVar2 < (uVar1 & 0x3ff) >> 4; uVar2 = uVar2 + 1) {
    uVar6 = *(uint *)(*(int *)(param_1 + 0xc) + uVar2 * 8 + 4);
    if (((int)(uVar6 << 7) < 0) && ((uVar6 & 0xffffff) == param_2)) {
      return *(undefined4 *)(*(int *)(param_1 + 0xc) + uVar2 * 8);
    }
  }
  uVar2 = ((uint)(uVar1 >> 10) | (uint)uVar1 << 0x16) + 0x4000000;
  *(ushort *)(param_1 + 0x2a) = (ushort)(uVar2 >> 0x16) | (uVar1 >> 10) << 10;
  if ((uVar2 >> 0x16 & 0x3f0) == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar3 = FUN_0004f588(*(undefined4 *)(param_1 + 0xc),(uVar2 >> 0x1a) << 3);
  *(int *)(param_1 + 0xc) = iVar3;
  if (iVar3 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar2 = (*(ushort *)(param_1 + 0x2a) & 0x3ff) >> 4;
  while (uVar2 = uVar2 - 1, uVar2 != 0) {
    iVar3 = *(int *)(param_1 + 0xc);
    iVar4 = *(int *)(iVar3 + uVar2 * 8 + -4);
    if ((iVar4 << 7 < 0) || (iVar4 << 6 < 0)) break;
    puVar5 = (undefined4 *)(iVar3 + uVar2 * 8);
    puVar7 = (undefined4 *)(uVar2 * 8 + -8 + iVar3);
    uVar8 = puVar7[1];
    *puVar5 = *puVar7;
    puVar5[1] = uVar8;
  }
  FUN_0004a5d2(*(int *)(param_1 + 0xc) + uVar2 * 8,8);
  uVar8 = FUN_0004a318(0xc);
  *(undefined4 *)(*(int *)(param_1 + 0xc) + uVar2 * 8) = uVar8;
  FUN_00050b06();
  iVar3 = uVar2 * 8 + 4;
  uVar6 = *(uint *)(*(int *)(param_1 + 0xc) + iVar3);
  *(uint *)(*(int *)(param_1 + 0xc) + iVar3) = uVar6 | 0x1000000;
  *(uint *)(*(int *)(param_1 + 0xc) + iVar3) = uVar6 & 0xff000000 | 0x1000000 | param_2 & 0xffffff;
  return *(undefined4 *)(*(int *)(param_1 + 0xc) + uVar2 * 8);
}

