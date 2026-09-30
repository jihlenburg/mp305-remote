/* Address: ram:00068e98; name: FUN_ram_00068e98; body bytes: 16 */

void FUN_ram_00068e98(int param_1)

{
  gp = 0x20004000;
  GATTServApp_SendServiceChangedInd(*(undefined2 *)(param_1 + 2),DAT_ram_20001a8e);
  return;
}

