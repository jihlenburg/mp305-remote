/* Address: ram:0005b4ec; name: FUN_ram_0005b4ec; body bytes: 248 */

undefined1 FUN_ram_0005b4ec(int param_1)

{
  byte bVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  undefined1 uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  
  gp = 0x20004000;
  iVar6 = *(int *)(param_1 + 0x114);
  uVar2 = *(ushort *)(iVar6 + 3);
  uVar10 = (uint)uVar2;
  uVar5 = 0x1e;
  if ((uVar10 - 6 & 0xffff) < 0xc7b) {
    uVar3 = *(ushort *)(iVar6 + 5);
    uVar9 = (uint)uVar3;
    uVar5 = 0x1e;
    if ((uVar9 < 0xc81) && (uVar10 <= uVar9)) {
      uVar7 = (uint)*(ushort *)(iVar6 + 7);
      if (uVar7 < 500) {
        uVar4 = *(ushort *)(iVar6 + 9);
        uVar8 = (uint)uVar4;
        if ((uVar8 < 0xc81) && ((int)((uVar7 + 1) * uVar10) < (int)(uVar8 << 3))) {
          bVar1 = *(byte *)(iVar6 + 0xb);
          if ((bVar1 == 0) || (bVar1 <= uVar9)) {
            uVar5 = false;
            if (((uVar10 == *(ushort *)(param_1 + 0x38)) && (uVar9 == uVar10)) &&
               (*(ushort *)(param_1 + 0x3a) == uVar7)) {
              uVar5 = *(ushort *)(param_1 + 0x3c) == uVar8;
            }
            *(ushort *)(param_1 + 0x58) = *(ushort *)(iVar6 + 7);
            *(ushort *)(param_1 + 0x72) = uVar2;
            *(ushort *)(param_1 + 0x74) = uVar3;
            *(ushort *)(param_1 + 0x5a) = uVar4;
            *(ushort *)(param_1 + 0x62) = (ushort)bVar1;
            *(undefined2 *)(param_1 + 100) = *(undefined2 *)(iVar6 + 0xc);
            tmos_memcpy(param_1 + 0x66,iVar6 + 0xe,0xc);
            *(undefined1 *)(param_1 + 0x1d) = 4;
          }
        }
      }
    }
  }
  return uVar5;
}

