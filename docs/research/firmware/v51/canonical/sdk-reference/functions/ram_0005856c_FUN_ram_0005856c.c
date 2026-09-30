/* Address: ram:0005856c; name: FUN_ram_0005856c; body bytes: 90 */

void FUN_ram_0005856c(int param_1)

{
  uint uVar1;
  
  gp = 0x20004000;
  FUN_ram_00062262();
  *(undefined1 *)(param_1 + 6) = 0xb0;
  tmos_stop_task(DAT_ram_20001b67,0x20);
  if (*(ushort *)(param_1 + 0x34) == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    uVar1 = 0x640 / *(ushort *)(param_1 + 0x34);
  }
  DAT_ram_20001d60 = DAT_ram_20001d60 + 1;
  if ((int)uVar1 <= (int)(uint)DAT_ram_20001d60) {
    FUN_ram_00042954();
    DAT_ram_20001d60 = 0;
  }
  return;
}

