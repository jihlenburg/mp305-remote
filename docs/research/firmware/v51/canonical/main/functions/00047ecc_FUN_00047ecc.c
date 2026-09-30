/* Address: 00047ecc; name: FUN_00047ecc; body bytes: 32 */

undefined4 FUN_00047ecc(byte *param_1)

{
  if (param_1 == (byte *)0x0) {
    return 3;
  }
  if (*param_1 - 0x20 < 0x60) {
    return 1;
  }
  if (0x7f < *param_1) {
    return 2;
  }
  return 0;
}

