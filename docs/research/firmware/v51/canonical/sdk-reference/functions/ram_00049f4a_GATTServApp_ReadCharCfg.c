/* Address: ram:00049f4a; name: GATTServApp_ReadCharCfg; body bytes: 24 */

undefined1 GATTServApp_ReadCharCfg(void)

{
  undefined1 uVar1;
  int iVar2;
  
  gp = 0x20004000;
  iVar2 = FUN_ram_00049dc2();
  if (iVar2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined1 *)(iVar2 + 2);
  }
  return uVar1;
}

