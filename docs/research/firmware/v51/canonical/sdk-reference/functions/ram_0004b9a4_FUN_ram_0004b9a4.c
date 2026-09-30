/* Address: ram:0004b9a4; name: FUN_ram_0004b9a4; body bytes: 428 */

int FUN_ram_0004b9a4(int param_1,short *param_2)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  short sVar6;
  uint uVar7;
  undefined2 auStack_42 [7];
  
  gp = 0x20004000;
  sVar6 = *(short *)(param_1 + 8);
  iVar3 = ATT_GetMTU(*(undefined2 *)(param_1 + 2));
  uVar2 = 0;
  while (((int)uVar2 < iVar3 + -3 &&
         (iVar4 = FUN_ram_0004aaf8(sVar6,*(undefined2 *)(param_1 + 10),param_1 + 0xd,
                                   *(undefined1 *)(param_1 + 0xc),auStack_42), iVar4 != 0))) {
    sVar6 = *(short *)(iVar4 + 10);
    iVar5 = FUN_ram_0004b654(*(undefined2 *)(param_1 + 2),*(undefined1 *)(iVar4 + 8),auStack_42[0]);
    if ((iVar5 != 0) ||
       (iVar5 = FUN_ram_0004b062(*(undefined2 *)(param_1 + 2),iVar4,auStack_42[0],DAT_ram_20001a44,
                                 &DAT_ram_20001a3a,0,iVar3 - 4U & 0xffff,
                                 *(undefined1 *)(param_1 + 4)), iVar5 != 0))
    goto joined_r0x0004bb4c;
    if (uVar2 == 0) {
      DAT_ram_20001b00 = GATT_bm_alloc(*(undefined2 *)(param_1 + 2),9,0xffff,0,0x13);
      if (DAT_ram_20001b00 == 0) {
        *param_2 = sVar6;
        gp = 0x20004000;
        return 0x11;
      }
      DAT_ram_20001afe = DAT_ram_20001a3a + 2;
    }
    else if ((uint)DAT_ram_20001afe != DAT_ram_20001a3a + 2) goto LAB_ram_0004ba62;
    if (iVar3 + -3 <= (int)(DAT_ram_20001a3a + uVar2)) break;
    *(char *)(DAT_ram_20001b00 + uVar2) = (char)*(undefined2 *)(iVar4 + 10);
    uVar1 = DAT_ram_20001a44;
    uVar7 = uVar2 + 2 & 0xffff;
    *(char *)(DAT_ram_20001b00 + (uVar2 + 1 & 0xffff)) =
         (char)((ushort)*(undefined2 *)(iVar4 + 10) >> 8);
    tmos_memcpy(DAT_ram_20001b00 + uVar7,uVar1,DAT_ram_20001a3a);
    uVar2 = DAT_ram_20001a3a + uVar7 & 0xffff;
    if (sVar6 != -1) {
      sVar6 = sVar6 + 1;
    }
  }
  iVar5 = 10;
joined_r0x0004bb4c:
  if (uVar2 == 0) {
    *param_2 = sVar6;
  }
  else {
LAB_ram_0004ba62:
    if (DAT_ram_20001afe == 0) {
      DAT_ram_20001afc = 0xffff;
    }
    else {
      DAT_ram_20001afc = (undefined2)(uVar2 / DAT_ram_20001afe);
    }
    iVar3 = FUN_ram_00043bda(*(undefined2 *)(param_1 + 2),&DAT_ram_20001afc);
    iVar5 = 0;
    if (iVar3 != 0) {
      iVar5 = 0x16;
    }
  }
  return iVar5;
}

