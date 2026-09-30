/* Address: ram:00004b9c; name: FUN_ram_00004b9c; body bytes: 22 */

void FUN_ram_00004b9c(void)

{
  gp = &DAT_ram_20002000;
  FUN_ram_00004628(1);
  FUN_ram_000042ac();
  usb_tx_queue_service(1);
  return;
}

