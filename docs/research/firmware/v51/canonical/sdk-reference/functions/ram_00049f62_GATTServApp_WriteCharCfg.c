/* Address: ram:00049f62; name: GATTServApp_WriteCharCfg; body bytes: 60 */

undefined4 GATTServApp_WriteCharCfg(undefined2 param_1,undefined4 param_2,undefined1 param_3)

{
  undefined2 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined2 *)FUN_ram_00049dc2();
  if (puVar1 == (undefined2 *)0x0) {
    puVar1 = (undefined2 *)FUN_ram_00049dc2(0xffff,param_2);
    if (puVar1 == (undefined2 *)0x0) {
      gp = 0x20004000;
      return 0x11;
    }
    *puVar1 = param_1;
  }
  *(undefined1 *)(puVar1 + 1) = param_3;
  return 0;
}

