/* Address: ram:00048dc4; name: FUN_ram_00048dc4; body bytes: 110 */

int FUN_ram_00048dc4(undefined4 param_1,undefined2 param_2,undefined2 param_3,undefined4 param_4,
                    undefined4 param_5)

{
  int iVar1;
  undefined2 uStack_2c;
  undefined2 uStack_2a;
  undefined2 uStack_28;
  int iStack_24;
  
  gp = 0x20004000;
  iStack_24 = GATT_bm_alloc(param_1,0x16,param_4,0,0x21);
  if (iStack_24 == 0) {
    iVar1 = 0x13;
  }
  else {
    uStack_28 = (undefined2)param_4;
    uStack_2c = param_2;
    uStack_2a = param_3;
    tmos_memcpy(iStack_24,param_5,param_4);
    iVar1 = FUN_ram_000438ac(param_1,&uStack_2c);
    if (iVar1 != 0) {
      FUN_ram_20000104(iStack_24);
    }
  }
  return iVar1;
}

