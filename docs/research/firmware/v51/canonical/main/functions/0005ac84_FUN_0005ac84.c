/* Address: 0005ac84; name: FUN_0005ac84; body bytes: 316 */

void FUN_0005ac84(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  undefined4 uVar11;
  undefined4 local_94 [16];
  int local_54;
  undefined4 local_44;
  undefined4 local_40;
  int local_3c;
  int local_38;
  int local_30;
  
  if (((*(char *)(DAT_2003a430 + 0x39) == '\x01') && (iVar1 = FUN_00040988(), iVar1 != 0)) &&
     (iVar1 = FUN_0004a23c(DAT_2003a430 + 0x264), iVar1 == 0)) {
    FUN_000661e0(DAT_2003a430);
    local_54 = *(int *)(DAT_2003a430 + 0x24);
    iVar1 = *(int *)(DAT_2003a430 + 0x1c);
    if (local_54 == iVar1) {
      iVar1 = *(int *)(DAT_2003a430 + 0x20);
    }
    local_30 = FUN_000408b0();
    iVar2 = FUN_00040960(DAT_2003a430);
    FUN_0001049c(local_94,0x40);
    for (uVar9 = 0; uVar9 < *(uint *)(DAT_2003a430 + 0x25c); uVar9 = uVar9 + 1 & 0xffff) {
      if (*(char *)(DAT_2003a430 + uVar9 + 0x23c) == '\0') {
        iVar3 = FUN_0004a118(DAT_2003a430 + 0x264);
        while (iVar10 = iVar3, iVar10 != 0) {
          iVar3 = FUN_0004a13c(DAT_2003a430 + 0x264,iVar10);
          iVar4 = FUN_0003da34(local_94,iVar10,DAT_2003a430 + uVar9 * 0x10 + 0x3c);
          if (iVar4 != -1) {
            for (iVar8 = 0; iVar8 < iVar4; iVar8 = (int)(char)((char)iVar8 + '\x01')) {
              puVar5 = (undefined4 *)FUN_0004a19e(DAT_2003a430 + 0x264,iVar10);
              uVar6 = local_94[iVar8 * 4 + 1];
              uVar7 = local_94[iVar8 * 4 + 2];
              uVar11 = local_94[iVar8 * 4 + 3];
              *puVar5 = local_94[iVar8 * 4];
              puVar5[1] = uVar6;
              puVar5[2] = uVar7;
              puVar5[3] = uVar11;
            }
            FUN_0004a2ac();
            FUN_00046bec(iVar10);
          }
        }
      }
    }
    local_44 = 0;
    local_40 = 0;
    local_3c = local_30 + -1;
    local_38 = iVar2 + -1;
    for (iVar2 = FUN_0004a118(DAT_2003a430 + 0x264); iVar2 != 0;
        iVar2 = FUN_0004a13c(DAT_2003a430 + 0x264,iVar2)) {
      FUN_0003db4c(iVar2,iVar2,&local_44);
      FUN_0004126c(local_54,iVar2,iVar1);
    }
    FUN_0004a0d8(DAT_2003a430 + 0x264);
  }
  return;
}

