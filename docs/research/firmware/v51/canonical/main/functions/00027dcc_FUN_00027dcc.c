/* Address: 00027dcc; name: FUN_00027dcc; body bytes: 268 */

undefined4 FUN_00027dcc(undefined4 param_1,int param_2,undefined4 param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  undefined4 *puVar11;
  int iVar12;
  int iVar13;
  byte *pbVar14;
  uint uVar15;
  int local_2c;
  
  puVar11 = *(undefined4 **)(param_2 + 0x48);
  local_2c = param_4;
  uVar1 = FUN_00040314(*(ushort *)(param_2 + 0x20) >> 8);
  iVar2 = (int)(((ulonglong)*(ushort *)(param_2 + 0x28) << 3) / (ulonglong)uVar1);
  uVar7 = *(uint *)(param_2 + 0x24) >> 0x10;
  iVar13 = *(ushort *)(param_2 + 0x28) * uVar7;
  uVar10 = uVar7 * iVar2;
  iVar2 = FUN_0004137c(&DAT_2003a518,*(uint *)(param_2 + 0x24) & 0xffff,uVar7,0xe,
                       iVar2 * 8 + 7U >> 3);
  if (iVar2 == 0) {
    return 0;
  }
  iVar12 = *(int *)(iVar2 + 0x10);
  if ((int)((*(uint *)(param_2 + 0x20) >> 0x10) << 0x1c) < 0) {
    iVar3 = puVar11[8];
  }
  else {
    if (*(char *)(param_2 + 0x10) == '\x01') {
      iVar3 = FUN_00036b7c(*puVar11,0xc,iVar12,iVar13,&local_2c);
      if ((iVar3 != 0) || (local_2c != iVar13)) {
        FUN_000413fe(iVar2);
        return 0;
      }
      goto LAB_00027e5a;
    }
    if (*(char *)(param_2 + 0x10) != '\0') goto LAB_00027e5a;
    iVar3 = *(int *)(param_2 + 0xc);
  }
  FUN_0004a404(iVar12,*(undefined4 *)(iVar3 + 0x10),iVar13);
LAB_00027e5a:
  if (*(ushort *)(param_2 + 0x20) >> 8 != 0xe) {
    pbVar14 = (byte *)(iVar12 + iVar13 + -1);
    puVar4 = (undefined1 *)(iVar12 + uVar10);
    uVar7 = 0;
    for (uVar9 = 0; puVar4 = puVar4 + -1, uVar9 < uVar10; uVar9 = uVar9 + 1) {
      uVar5 = (uint)(*pbVar14 >> uVar7) & (1 << (uVar1 & 0xff)) - 1U & 0xff;
      uVar6 = uVar5;
      uVar8 = uVar1;
      if (uVar5 != 0) {
        for (; uVar8 < 8; uVar8 = uVar8 + uVar1 & 0xff) {
          uVar15 = 8 - uVar8;
          uVar6 = uVar5 << (uVar15 & 0xff) & 0xff | uVar6;
        }
      }
      *puVar4 = (char)uVar6;
      uVar7 = uVar7 + uVar1 & 0xff;
      if (7 < uVar7) {
        uVar7 = 0;
        pbVar14 = pbVar14 + -1;
      }
    }
  }
  puVar11[7] = iVar2;
  *(int *)(param_2 + 0x2c) = iVar2;
  return 1;
}

