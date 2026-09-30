/* Address: ram:0004904e; name: GATT_ReliableWrites; body bytes: 218 */

int GATT_ReliableWrites(undefined4 param_1,undefined2 *param_2,uint param_3,undefined1 param_4,
                       undefined4 param_5)

{
  int iVar1;
  ushort *puVar2;
  uint uVar3;
  undefined4 local_30;
  undefined1 auStack_2c [4];
  int iStack_28;
  undefined1 uStack_24;
  undefined1 uStack_23;
  undefined1 uStack_22;
  
  gp = 0x20004000;
  iVar1 = 2;
  if ((param_2 != (undefined2 *)0x0) && (param_3 != 0)) {
    iVar1 = ATT_GetMTU();
    puVar2 = param_2 + 2;
    uVar3 = 0;
    do {
      if (iVar1 + -4 <= (int)(uint)*puVar2) {
        gp = 0x20004000;
        return 0x1b;
      }
      uVar3 = uVar3 + 1 & 0xff;
      puVar2 = puVar2 + 6;
    } while (param_3 != uVar3);
    iVar1 = FUN_ram_0004957c(param_1,&local_30);
    if (iVar1 == 0) {
      iVar1 = 0x13;
      iStack_28 = FUN_ram_20000040(param_3 * 0xc,0x4701);
      if (iStack_28 != 0) {
        tmos_memcpy(iStack_28,param_2,param_3 * 0xc);
        iVar1 = FUN_ram_00048dc4(param_1,*param_2,param_2[1],param_2[2],*(undefined4 *)(param_2 + 4)
                                );
        if (iVar1 == 0) {
          auStack_2c[0] = 1;
          uStack_24 = (undefined1)param_3;
          uStack_23 = 0;
          uStack_22 = param_4;
          FUN_ram_0004972e(local_30,auStack_2c,0x17,&LAB_ram_00043868,param_5);
        }
        else {
          FUN_ram_20000104(iStack_28);
        }
      }
    }
  }
  return iVar1;
}

