/* Address: 00059fec; name: FUN_00059fec; body bytes: 122 */

void FUN_00059fec(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  if ((int)((uint)*(byte *)(param_1 + 0x70) << 0x1d) < 0) {
    FUN_000491e8(*(undefined4 *)(param_1 + 0x2c));
    uVar1 = FUN_00051c88();
    if (uVar1 != 0) {
      uVar2 = FUN_0005231c(param_1);
      iVar3 = FUN_00050a64();
      iVar4 = FUN_0004a318(uVar1 * iVar3 + 1);
      for (uVar5 = 0; uVar5 < uVar1; uVar5 = uVar5 + 1) {
        FUN_0004a404(uVar5 * iVar3 + iVar4,uVar2,iVar3);
      }
      *(undefined1 *)(iVar4 + iVar3 * uVar5) = 0;
      FUN_00049974(*(undefined4 *)(param_1 + 0x2c),iVar4);
      FUN_00046bec(iVar4);
      FUN_0003c97c(param_1,&DAT_0005a071);
      FUN_0005a550(param_1);
      return;
    }
  }
  return;
}

