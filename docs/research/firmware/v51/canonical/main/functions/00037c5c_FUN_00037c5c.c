/* Address: 00037c5c; name: FUN_00037c5c; body bytes: 178 */

int FUN_00037c5c(int param_1,uint param_2)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined4 *puVar6;
  uint uVar7;
  undefined4 *puVar8;
  
  uVar1 = *(ushort *)(param_1 + 0x2a);
  uVar2 = 0;
  uVar5 = (uVar1 & 0x3ff) >> 4;
  while ((uVar2 < uVar5 &&
         ((uVar7 = *(uint *)(*(int *)(param_1 + 0xc) + uVar2 * 8 + 4), -1 < (int)(uVar7 << 6) ||
          ((uVar7 & 0xffffff) != param_2))))) {
    uVar2 = uVar2 + 1;
  }
  if (uVar5 == uVar2) {
    uVar2 = ((uint)(uVar1 >> 10) | (uint)uVar1 << 0x16) + 0x4000000;
    *(ushort *)(param_1 + 0x2a) = (ushort)(uVar2 >> 0x16) | (uVar1 >> 10) << 10;
    if ((uVar2 >> 0x16 & 0x3f0) == 0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    uVar4 = FUN_0004f588(*(undefined4 *)(param_1 + 0xc),(uVar2 >> 0x1a) << 3);
    *(undefined4 *)(param_1 + 0xc) = uVar4;
    uVar2 = (*(ushort *)(param_1 + 0x2a) & 0x3ff) >> 4;
    while (uVar2 = uVar2 - 1, uVar2 != 0) {
      puVar6 = (undefined4 *)(*(int *)(param_1 + 0xc) + uVar2 * 8);
      puVar8 = (undefined4 *)(uVar2 * 8 + -8 + *(int *)(param_1 + 0xc));
      uVar4 = puVar8[1];
      *puVar6 = *puVar8;
      puVar6[1] = uVar4;
    }
    FUN_0004a5d2(*(undefined4 *)(param_1 + 0xc),8);
    uVar4 = FUN_0004a318(0xc);
    **(undefined4 **)(param_1 + 0xc) = uVar4;
    FUN_00050b06();
    uVar2 = *(uint *)(*(int *)(param_1 + 0xc) + 4);
    *(uint *)(*(int *)(param_1 + 0xc) + 4) = uVar2 | 0x2000000;
    *(uint *)(*(int *)(param_1 + 0xc) + 4) = uVar2 & 0xff000000 | 0x2000000 | param_2 & 0xffffff;
    iVar3 = *(int *)(param_1 + 0xc);
  }
  else {
    iVar3 = *(int *)(param_1 + 0xc) + uVar2 * 8;
  }
  return iVar3;
}

