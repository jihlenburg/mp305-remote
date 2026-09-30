/* Address: ram:00049128; name: FUN_ram_00049128; body bytes: 148 */

int FUN_ram_00049128(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined2 uStack_28;
  undefined2 uStack_26;
  undefined1 *puStack_24;
  
  gp = 0x20004000;
  iVar2 = FUN_ram_0004aaf8(1,0xffff,&DAT_ram_0006c664,2,0);
  iVar1 = 1;
  if (iVar2 != 0) {
    puStack_24 = (undefined1 *)GATT_bm_alloc(param_1,0x1d,4,0,0x23);
    iVar1 = 0x15;
    if (puStack_24 != (undefined1 *)0x0) {
      uStack_28 = *(undefined2 *)(iVar2 + 10);
      uStack_26 = 4;
      *puStack_24 = 1;
      puStack_24[1] = 0;
      puStack_24[2] = 0xff;
      puStack_24[3] = 0xff;
      iVar1 = GATT_Indication(param_1,&uStack_28,0,param_2);
      if (iVar1 != 0) {
        FUN_ram_20000104(puStack_24);
      }
    }
  }
  return iVar1;
}

