/* Address: 0001fc24; name: FUN_0001fc24; body bytes: 98 */

undefined4 FUN_0001fc24(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  
  uVar1 = 0;
  if (*(char *)(param_1 + 1) == '\0') {
    iVar2 = (uint)*(byte *)(param_1 + 2) + (uint)*(byte *)(param_1 + 3) * 0x100 +
            (uint)*(byte *)(param_1 + 4) * 0x10000 + (uint)*(byte *)(param_1 + 5) * 0x1000000;
    uVar3 = (uint)*(byte *)(param_1 + 6) + (uint)*(byte *)(param_1 + 7) * 0x100 +
            (uint)*(byte *)(param_1 + 8) * 0x10000 + (uint)*(byte *)(param_1 + 9) * 0x1000000;
    if (iVar2 + uVar3 < 0x800001) {
      FUN_0001bdc6(0);
      do {
        FUN_0001bdc6(iVar2);
        uVar3 = uVar3 - 0x10000;
        iVar2 = iVar2 + 0x10000;
      } while (0xffff < uVar3);
      if (uVar3 != 0) {
        FUN_0001bdc6(iVar2);
      }
      uVar1 = 1;
    }
  }
  return uVar1;
}

