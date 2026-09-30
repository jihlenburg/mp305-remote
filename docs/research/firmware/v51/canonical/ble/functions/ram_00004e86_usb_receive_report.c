/* Address: ram:00004e86; name: usb_receive_report; body bytes: 68 */

/* Reads length at HID byte 1 and feeds bytes starting at byte 2 into stream decoder. */

void usb_receive_report(void)

{
  int iVar1;
  int iVar2;
  
  gp = &DAT_ram_20002000;
  iVar2 = (uint)*(byte *)(DAT_ram_20002f54 + 1) + DAT_ram_20002f54;
  for (iVar1 = DAT_ram_20002f54; iVar1 != iVar2; iVar1 = iVar1 + 1) {
    FUN_ram_0000384e(1,*(undefined1 *)(iVar1 + 2));
  }
  DAT_ram_20002f90 = usb_send_report;
  return;
}

