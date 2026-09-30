/* Address: ram:0004a09c; name: GATTServApp_SendServiceChangedInd; body bytes: 56 */

undefined4 GATTServApp_SendServiceChangedInd(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  uVar1 = GATTServApp_ReadCharCfg(param_1,DAT_ram_20001a40);
  if ((uVar1 & 2) != 0) {
    uVar2 = FUN_ram_00049128(param_1,param_2);
    return uVar2;
  }
  return 1;
}

