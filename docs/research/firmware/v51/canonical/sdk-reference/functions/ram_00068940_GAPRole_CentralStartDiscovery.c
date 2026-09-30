/* Address: ram:00068940; name: GAPRole_CentralStartDiscovery; body bytes: 40 */

void GAPRole_CentralStartDiscovery(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 uStack_14;
  undefined1 uStack_13;
  undefined1 uStack_12;
  undefined1 uStack_11;
  
  gp = 0x20004000;
  uStack_14 = DAT_ram_20001a7c;
  uStack_13 = param_1;
  uStack_12 = param_2;
  uStack_11 = param_3;
  FUN_ram_00046844(&uStack_14);
  return;
}

