/* Address: ram:0004934a; name: FUN_ram_0004934a; body bytes: 472 */

undefined4 FUN_ram_0004934a(undefined2 *param_1,int param_2,ushort *param_3)

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  short *psVar4;
  ushort uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  short sStack_38;
  ushort uStack_36;
  undefined *puStack_34;
  undefined1 uStack_32;
  
  gp = 0x20004000;
  if (param_2 == 9) {
    uVar1 = *param_3;
    uVar2 = param_3[1];
    *(char *)(param_1 + 0x12) = *(char *)(param_1 + 0x12) + '\x01';
    uVar5 = *(ushort *)(((uint)uVar2 * (uVar1 - 1) & 0xffff) + *(int *)(param_3 + 2));
    if (*(char *)(param_1 + 6) == '\x01') {
      *param_3 = 0;
      uVar8 = 0;
      for (uVar7 = 0; uVar7 < ((uint)uVar1 * (uint)uVar2 & 0xffff);
          uVar7 = uVar7 + param_3[1] & 0xffff) {
        iVar3 = ATT_CompareUUID((int)param_1 + 0x13,*(undefined1 *)(param_1 + 9),
                                uVar7 + 5 + *(int *)(param_3 + 2),param_3[1] - 5);
        if (iVar3 != 0) {
          if (uVar8 != uVar7) {
            tmos_memcpy(*(int *)(param_3 + 2) + uVar8,*(int *)(param_3 + 2) + uVar7,param_3[1]);
          }
          uVar8 = uVar8 + param_3[1] & 0xffff;
          *param_3 = *param_3 + 1;
        }
      }
    }
  }
  else {
    if (((char)param_3[2] == '\n') && (*(char *)(param_1 + 0x12) != '\0')) {
      gp = 0x20004000;
      return 0;
    }
    iVar6 = (int)param_1 + 0x13;
    iVar3 = ATT_CompareUUID(&DAT_ram_0006c65c,2,iVar6,*(undefined1 *)(param_1 + 9));
    if (((((iVar3 != 0) ||
          (iVar3 = ATT_CompareUUID(&DAT_ram_0006c660,2,iVar6,*(undefined1 *)(param_1 + 9)),
          iVar3 != 0)) ||
         (iVar3 = ATT_CompareUUID(&DAT_ram_0006c654,2,iVar6,*(undefined1 *)(param_1 + 9)),
         iVar3 != 0)) ||
        ((iVar3 = ATT_CompareUUID(&DAT_ram_0006c640,2,iVar6,*(undefined1 *)(param_1 + 9)),
         iVar3 != 0 || (0xf < (byte)param_3[2])))) ||
       ((0x9124U >> ((byte)param_3[2] & 0x1f) & 1) == 0)) {
      gp = 0x20004000;
      return 1;
    }
    *(char *)(param_1 + 0x12) = *(char *)(param_1 + 0x12) + '\x01';
    uVar5 = param_3[1];
  }
  if ((uVar5 != 0xffff) && (uVar5 < (ushort)param_1[8])) {
    param_1[7] = uVar5 + 1;
    psVar4 = param_1 + 7;
    if (*(char *)(param_1 + 6) == '\x01') {
      puStack_34 = &medeleg;
      uStack_32 = 0x28;
      psVar4 = &sStack_38;
      sStack_38 = uVar5 + 1;
      uStack_36 = param_1[8];
    }
    FUN_ram_000436ec(*param_1,psVar4);
    FUN_ram_00042194(*(undefined1 *)(param_1 + 4),48000);
    gp = 0x20004000;
    return 0x16;
  }
  return 0;
}

