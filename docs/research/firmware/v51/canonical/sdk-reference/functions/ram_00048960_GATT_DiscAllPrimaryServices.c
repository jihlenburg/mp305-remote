/* Address: ram:00048960; name: GATT_DiscAllPrimaryServices; body bytes: 90 */

int GATT_DiscAllPrimaryServices(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined2 uStack_24;
  undefined1 uStack_22;
  
  gp = 0x20004000;
  uStack_28 = 0xffff0001;
  uStack_24 = 2;
  uStack_22 = 0x28;
  iVar1 = FUN_ram_0004957c(param_1,&uStack_2c);
  if ((iVar1 == 0) && (iVar1 = FUN_ram_000437d2(param_1,&uStack_28), iVar1 == 0)) {
    FUN_ram_0004972e(uStack_2c,&uStack_28,0x11,&LAB_ram_0004379e,param_2);
  }
  return iVar1;
}

