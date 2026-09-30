/* Address: 0004ab24; name: FUN_0004ab24; body bytes: 228 */

void FUN_0004ab24(int param_1,int param_2,uint param_3)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  
  if (0x3e < (*(ushort *)(param_1 + 0x2a) & 0x3ff) >> 4) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  FUN_000637cc(param_1,param_3,0xff,0);
  if (((param_2 != 0) && ((param_3 & 0xff0000) == 0)) &&
     (iVar2 = FUN_0006078c(param_2,0x20), iVar2 != 0)) {
    FUN_0004d3d8(param_1);
  }
  FUN_0004e0f6(param_1,param_2,param_3);
  uVar1 = *(ushort *)(param_1 + 0x2a);
  uVar5 = 0;
  while ((uVar5 < (uVar1 & 0x3ff) >> 4 &&
         ((iVar2 = *(int *)(*(int *)(param_1 + 0xc) + uVar5 * 8 + 4), iVar2 << 6 < 0 ||
          (iVar2 << 7 < 0))))) {
    uVar5 = uVar5 + 1;
  }
  uVar3 = ((uint)(uVar1 >> 10) | (uint)uVar1 << 0x16) + 0x4000000;
  *(ushort *)(param_1 + 0x2a) = (ushort)(uVar3 >> 0x16) | (uVar1 >> 10) << 10;
  if ((uVar3 >> 0x16 & 0x3f0) != 0) {
    iVar2 = FUN_0004f588(*(undefined4 *)(param_1 + 0xc),(uVar3 >> 0x1a) << 3);
    *(int *)(param_1 + 0xc) = iVar2;
    if (iVar2 != 0) {
      uVar3 = (*(ushort *)(param_1 + 0x2a) & 0x3ff) >> 4;
      while (uVar3 = uVar3 - 1, uVar5 < uVar3) {
        puVar6 = (undefined4 *)(uVar3 * 8 + -8 + *(int *)(param_1 + 0xc));
        puVar4 = (undefined4 *)(*(int *)(param_1 + 0xc) + uVar3 * 8);
        uVar7 = puVar6[1];
        *puVar4 = *puVar6;
        puVar4[1] = uVar7;
      }
      FUN_0004a5d2(*(int *)(param_1 + 0xc) + uVar5 * 8,8);
      *(int *)(*(int *)(param_1 + 0xc) + uVar5 * 8) = param_2;
      iVar2 = uVar5 * 8 + 4;
      *(uint *)(*(int *)(param_1 + 0xc) + iVar2) =
           *(uint *)(*(int *)(param_1 + 0xc) + iVar2) & 0xff000000 | param_3 & 0xffffff;
      FUN_0004dedc(param_1,param_3,0xff);
      return;
    }
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

