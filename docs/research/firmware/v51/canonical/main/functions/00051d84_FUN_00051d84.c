/* Address: 00051d84; name: FUN_00051d84; body bytes: 50 */

undefined4 FUN_00051d84(byte *param_1)

{
  byte bVar1;
  
  bVar1 = *param_1;
  if (-1 < (int)((uint)bVar1 << 0x18)) {
    return 1;
  }
  if (bVar1 >> 5 == 6) {
    return 2;
  }
  if (bVar1 >> 4 == 0xe) {
    return 3;
  }
  if (bVar1 >> 3 == 0x1e) {
    return 4;
  }
  return 0;
}

