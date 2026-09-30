/* Address: ram:00061c80; name: BLE_ReadRssi; body bytes: 18 */

int BLE_ReadRssi(void)

{
  gp = 0x20004000;
  return (int)(char)(*(uint *)(DAT_ram_20001e88 + 0x30) >> 0xf);
}

