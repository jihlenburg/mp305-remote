/* Address: ram:00003e1a; name: usb_tx_queue_service; body bytes: 188 */

/* Splits outgoing frames into chunks of at most 62 bytes. */

void usb_tx_queue_service(void)

{
  byte bVar1;
  
  gp = &DAT_ram_20002000;
  if ((DAT_ram_20003a49 != '\0') && (DAT_ram_20003a4a != '\0')) {
    if ((byte)(&DAT_ram_20003a44)[DAT_ram_20003a4b] < 0x3f) {
      usb_send_report(&DAT_ram_20003644 + CONCAT11(DAT_ram_20003a4b,DAT_ram_20003a4c));
      DAT_ram_20003a4c = '\0';
      bVar1 = DAT_ram_20003a4b + 1;
      DAT_ram_20003a4a = DAT_ram_20003a4a + -1;
      DAT_ram_20003a4b = DAT_ram_20003a4b + 1;
      if (3 < bVar1) {
        DAT_ram_20003a4b = 0;
      }
    }
    else {
      usb_send_report(&DAT_ram_20003644 + CONCAT11(DAT_ram_20003a4b,DAT_ram_20003a4c),0x3e);
      (&DAT_ram_20003a44)[DAT_ram_20003a4b] = (&DAT_ram_20003a44)[DAT_ram_20003a4b] + -0x3e;
      DAT_ram_20003a4c = DAT_ram_20003a4c + '>';
    }
    return;
  }
  return;
}

