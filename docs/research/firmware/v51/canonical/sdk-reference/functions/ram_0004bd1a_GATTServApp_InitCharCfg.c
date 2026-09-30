/* Address: ram:0004bd1a; name: GATTServApp_InitCharCfg; body bytes: 40 */

void GATTServApp_InitCharCfg(int param_1,undefined4 param_2)

{
  undefined2 *puVar1;
  
  gp = 0x20004000;
  if (param_1 == 0xffff) {
    FUN_ram_00049e22(param_2);
    return;
  }
  puVar1 = (undefined2 *)FUN_ram_00049dc2();
  if (puVar1 != (undefined2 *)0x0) {
    *puVar1 = 0xffff;
    *(undefined1 *)(puVar1 + 1) = 0;
  }
  return;
}

