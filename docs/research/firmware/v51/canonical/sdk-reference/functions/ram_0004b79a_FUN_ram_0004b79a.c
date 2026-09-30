/* Address: ram:0004b79a; name: FUN_ram_0004b79a; body bytes: 522 */

int FUN_ram_0004b79a(int param_1,undefined2 *param_2)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined1 *puVar7;
  uint uVar8;
  undefined2 uStack_44;
  undefined1 auStack_42 [14];
  
  gp = 0x20004000;
  iVar4 = ATT_GetMTU(*(undefined2 *)(param_1 + 2));
  iVar5 = FUN_ram_0004aaf8(*(undefined2 *)(param_1 + 8),*(undefined2 *)(param_1 + 10),param_1 + 0xd,
                           *(undefined1 *)(param_1 + 0xc),&uStack_44);
  uVar2 = 0;
  do {
    if (iVar5 == 0) {
      iVar6 = 0;
LAB_ram_0004b94e:
      if (uVar2 == 0) {
        *param_2 = *(undefined2 *)(param_1 + 8);
        if (iVar6 == 0) {
          iVar6 = 10;
        }
      }
      else {
LAB_ram_0004b85e:
        if (DAT_ram_20001afe == 0) {
          DAT_ram_20001afc = 0xffff;
        }
        else {
          DAT_ram_20001afc = (undefined2)(uVar2 / DAT_ram_20001afe);
        }
        iVar4 = FUN_ram_00043d16(*(undefined2 *)(param_1 + 2),&DAT_ram_20001afc);
        iVar6 = 0;
        if (iVar4 != 0) {
          iVar6 = 0x16;
        }
      }
      return iVar6;
    }
    iVar6 = FUN_ram_0004b654(*(undefined2 *)(param_1 + 2),*(undefined1 *)(iVar5 + 8),uStack_44);
    if ((iVar6 != 0) ||
       (iVar6 = FUN_ram_0004b062(*(undefined2 *)(param_1 + 2),iVar5,uStack_44,DAT_ram_20001a44,
                                 &DAT_ram_20001a3a,0,iVar4 - 6U & 0xffff,
                                 *(undefined1 *)(param_1 + 4)), iVar6 != 0)) {
      *param_2 = *(undefined2 *)(iVar5 + 10);
      goto LAB_ram_0004b94e;
    }
    if (uVar2 == 0) {
      DAT_ram_20001b00 = GATT_bm_alloc(*(undefined2 *)(param_1 + 2),0x11,0xffff,0,0x12);
      if (DAT_ram_20001b00 == 0) {
        *param_2 = *(undefined2 *)(iVar5 + 10);
        gp = 0x20004000;
        return 0x11;
      }
      DAT_ram_20001afe = DAT_ram_20001a3a + 4;
    }
    else if (((uint)DAT_ram_20001afe != DAT_ram_20001a3a + 4) ||
            (iVar4 + -5 <= (int)(DAT_ram_20001afe + uVar2))) goto LAB_ram_0004b85e;
    *(char *)(DAT_ram_20001b00 + uVar2) = (char)*(undefined2 *)(iVar5 + 10);
    *(char *)(DAT_ram_20001b00 + (uVar2 + 1 & 0xffff)) =
         (char)((ushort)*(undefined2 *)(iVar5 + 10) >> 8);
    iVar5 = FUN_ram_0004afa0(iVar5,*(undefined2 *)(param_1 + 10),uStack_44,auStack_42);
    uVar1 = DAT_ram_20001a44;
    uVar8 = uVar2 + 3 & 0xffff;
    uVar3 = uVar2 + 4 & 0xffff;
    puVar7 = (undefined1 *)((uVar2 + 2 & 0xffff) + DAT_ram_20001b00);
    if (iVar5 == 0) {
      *puVar7 = 0xff;
      uVar1 = DAT_ram_20001a44;
      *(undefined1 *)(uVar8 + DAT_ram_20001b00) = 0xff;
      tmos_memcpy(DAT_ram_20001b00 + uVar3,uVar1,DAT_ram_20001a3a);
      uVar2 = uVar3 + DAT_ram_20001a3a & 0xffff;
      goto LAB_ram_0004b94e;
    }
    *puVar7 = (char)auStack_42._0_2_;
    *(char *)(uVar8 + DAT_ram_20001b00) = SUB21(auStack_42._0_2_,1);
    tmos_memcpy(DAT_ram_20001b00 + uVar3,uVar1,DAT_ram_20001a3a);
    uVar2 = uVar3 + DAT_ram_20001a3a & 0xffff;
  } while( true );
}

