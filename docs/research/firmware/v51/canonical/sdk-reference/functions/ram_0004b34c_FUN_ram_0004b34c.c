/* Address: ram:0004b34c; name: FUN_ram_0004b34c; body bytes: 354 */

int FUN_ram_0004b34c(int param_1,undefined2 *param_2)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined2 auStack_42 [7];
  
  gp = 0x20004000;
  iVar2 = ATT_GetMTU(*(undefined2 *)(param_1 + 2));
  uVar4 = 0;
  while( true ) {
    if ((*(ushort *)(param_1 + 0xc) <= uVar4) || ((int)(iVar2 - 1U) <= (int)(uint)DAT_ram_20001afc))
    {
      iVar3 = FUN_ram_00043cde(*(undefined2 *)(param_1 + 2),&DAT_ram_20001afc);
      iVar2 = 0;
      if (iVar3 != 0) {
        iVar2 = 0x16;
      }
      return iVar2;
    }
    uVar1 = *(undefined2 *)(*(int *)(param_1 + 8) + uVar4 * 2);
    iVar3 = GATT_FindHandle(uVar1,auStack_42);
    if (iVar3 == 0) break;
    iVar3 = FUN_ram_0004b062(*(undefined2 *)(param_1 + 2),iVar3,auStack_42[0],DAT_ram_20001a44,
                             &DAT_ram_20001a3a,0,iVar2 - 1U & 0xffff,*(undefined1 *)(param_1 + 4));
    if (iVar3 != 0) {
      *param_2 = uVar1;
      goto LAB_ram_0004b3e6;
    }
    if ((DAT_ram_20001b00 == 0) &&
       (DAT_ram_20001b00 = GATT_bm_alloc(*(undefined2 *)(param_1 + 2),0xf,0xffff,0,0x14),
       DAT_ram_20001b00 == 0)) {
      *param_2 = uVar1;
      gp = 0x20004000;
      return 0x11;
    }
    if (iVar2 <= (int)((uint)DAT_ram_20001a3a + (uint)DAT_ram_20001afc)) {
      DAT_ram_20001a3a = ~DAT_ram_20001afc + (short)iVar2;
    }
    tmos_memcpy(DAT_ram_20001b00 + (uint)DAT_ram_20001afc,DAT_ram_20001a44,DAT_ram_20001a3a);
    uVar4 = uVar4 + 1 & 0xffff;
    DAT_ram_20001afc = DAT_ram_20001afc + DAT_ram_20001a3a;
  }
  *param_2 = uVar1;
  iVar3 = 1;
LAB_ram_0004b3e6:
  if (DAT_ram_20001b00 == 0) {
    gp = 0x20004000;
    return iVar3;
  }
  FUN_ram_20000104();
  gp = 0x20004000;
  return iVar3;
}

