/* Address: ram:00048a0e; name: GATT_FindIncludedServices; body bytes: 42 */

void GATT_FindIncludedServices(undefined4 param_1,undefined2 param_2,undefined2 param_3)

{
  undefined2 uStack_28;
  undefined2 uStack_26;
  undefined2 uStack_24;
  undefined1 uStack_22;
  
  gp = 0x20004000;
  uStack_24 = 0x202;
  uStack_22 = 0x28;
  uStack_28 = param_2;
  uStack_26 = param_3;
  FUN_ram_0004864e(param_1,&uStack_28,0);
  return;
}

