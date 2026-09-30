/* Address: ram:00061d46; name: BLE_ReadCfo; body bytes: 34 */

int BLE_ReadCfo(void)

{
  ushort uVar1;
  
  gp = 0x20004000;
  uVar1 = (ushort)((*(uint *)(DAT_ram_20001e88 + 0x30) & 0x7fff) >> 5);
  if ((int)(*(uint *)(DAT_ram_20001e88 + 0x30) << 0x11) < 0) {
    uVar1 = uVar1 | 0xfc00;
  }
  return (int)(short)uVar1;
}

