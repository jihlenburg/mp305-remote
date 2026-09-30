/* Address: ram:00004eca; name: usb_send_report; body bytes: 114 */

/* Writes report ID 2 at byte 0, chunk length at byte 1, data at byte 2, sends 64 bytes. */

void usb_send_report(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = DAT_ram_20002f54;
  gp = &DAT_ram_20002000;
  FUN_ram_00001d1a(DAT_ram_20002f54 + 0x42,0,0x3e);
  for (uVar3 = 0; iVar2 = DAT_ram_20002f54, uVar3 < param_2; uVar3 = uVar3 + 1 & 0xff) {
    *(undefined1 *)(iVar1 + uVar3 + 0x42) = *(undefined1 *)(param_1 + uVar3);
  }
  *(char *)(DAT_ram_20002f54 + 0x41) = (char)param_2;
  *(undefined1 *)(iVar2 + 0x40) = 2;
  FUN_ram_00002a5e(0x40);
  DAT_ram_20003a49 = 0;
  return;
}

