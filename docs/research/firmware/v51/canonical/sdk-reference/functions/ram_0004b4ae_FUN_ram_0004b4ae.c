/* Address: ram:0004b4ae; name: FUN_ram_0004b4ae; body bytes: 422 */

undefined4 FUN_ram_0004b4ae(int param_1,undefined2 *param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined1 *puVar6;
  int iVar7;
  uint uVar8;
  undefined2 uStack_34;
  undefined1 auStack_32 [2];
  
  gp = 0x20004000;
  iVar2 = ATT_GetMTU(*(undefined2 *)(param_1 + 2));
  iVar3 = FUN_ram_0004aaf8(*(undefined2 *)(param_1 + 8),*(undefined2 *)(param_1 + 10),param_1 + 0xd,
                           *(undefined1 *)(param_1 + 0xc),&uStack_34);
  uVar1 = 0;
  do {
    while( true ) {
      if ((iVar3 == 0) || (iVar2 + -5 <= (int)uVar1)) goto LAB_ram_0004b558;
      iVar4 = FUN_ram_0004b062(*(undefined2 *)(param_1 + 2),iVar3,uStack_34,DAT_ram_20001a44,
                               &DAT_ram_20001a3a,0,iVar2 - 7U & 0xffff,*(undefined1 *)(param_1 + 4))
      ;
      if ((iVar4 == 0) &&
         ((*(short *)(param_1 + 0x10) == DAT_ram_20001a3a &&
          (iVar4 = tmos_memcmp(*(undefined4 *)(param_1 + 0x14),DAT_ram_20001a44), iVar4 != 0)))) {
        iVar4 = DAT_ram_20001b00;
        if ((DAT_ram_20001b00 == 0) &&
           (iVar4 = GATT_bm_alloc(*(undefined2 *)(param_1 + 2),7,0xffff,0,0x11), iVar4 == 0)) {
          *param_2 = *(undefined2 *)(param_1 + 8);
          gp = 0x20004000;
          return 0x11;
        }
        DAT_ram_20001b00 = iVar4;
        uVar8 = (uint)*(ushort *)(iVar3 + 10);
      }
      else {
        uVar8 = 0;
      }
      iVar3 = FUN_ram_0004afa0(iVar3,*(undefined2 *)(param_1 + 10),uStack_34,auStack_32);
      if (uVar8 == 0) break;
      *(char *)(DAT_ram_20001b00 + uVar1) = (char)uVar8;
      *(char *)(DAT_ram_20001b00 + uVar1 + 1) = (char)(uVar8 >> 8);
      iVar4 = uVar1 + 2;
      iVar7 = uVar1 + 3;
      uVar1 = uVar1 + 4 & 0xffff;
      puVar6 = (undefined1 *)(iVar4 + DAT_ram_20001b00);
      if (iVar3 == 0) {
        *puVar6 = 0xff;
        *(undefined1 *)(iVar7 + DAT_ram_20001b00) = 0xff;
        goto LAB_ram_0004b558;
      }
      *puVar6 = auStack_32[0];
      *(char *)(iVar7 + DAT_ram_20001b00) = auStack_32[1];
    }
  } while (iVar3 != 0);
LAB_ram_0004b558:
  if (uVar1 == 0) {
    uVar5 = 10;
    *param_2 = *(undefined2 *)(param_1 + 8);
  }
  else {
    DAT_ram_20001afc = (undefined2)(uVar1 >> 2);
    iVar2 = FUN_ram_00043b3e(*(undefined2 *)(param_1 + 2),&DAT_ram_20001afc);
    uVar5 = 0;
    if (iVar2 != 0) {
      uVar5 = 0x16;
    }
  }
  return uVar5;
}

