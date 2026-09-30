/* Address: ram:000603de; name: FUN_ram_000603de; body bytes: 190 */

void FUN_ram_000603de(void)

{
  undefined1 uVar1;
  int iVar2;
  
  iVar2 = DAT_ram_20001dd8;
  gp = 0x20004000;
  if ((DAT_ram_20001e9d != '\0') && (DAT_ram_20001e9c == '\x02')) {
    DAT_ram_20001e9d = '\0';
  }
  if ((byte)(DAT_ram_20001e9b - 7U) < 2) {
    DAT_ram_20001e9c = DAT_ram_20001e9b;
    DAT_ram_20001e9d = '\x01';
  }
  FUN_ram_00062262();
  *(undefined2 *)(iVar2 + 10) = 0;
  *(undefined1 *)(iVar2 + 8) = 0;
  FUN_ram_20000104(*(undefined4 *)(iVar2 + 0x44));
  uVar1 = DAT_ram_20001b67;
  *(undefined2 *)(iVar2 + 0x40) = 0;
  *(undefined4 *)(iVar2 + 0x44) = 0;
  *(undefined4 *)(iVar2 + 0x48) = 0;
  tmos_stop_task(uVar1,4);
  tmos_stop_task(DAT_ram_20001b67,8);
  if (*(char *)(iVar2 + 0x31) != -1) {
    FUN_ram_00042494();
    *(undefined1 *)(iVar2 + 0x31) = 0xff;
  }
  if (*(char *)(iVar2 + 0x30) != -1) {
    FUN_ram_00042494();
    *(undefined1 *)(iVar2 + 0x30) = 0xff;
  }
  return;
}

