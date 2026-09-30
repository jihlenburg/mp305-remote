/* Address: 0003a5c8; name: FUN_0003a5c8; body bytes: 20 */

uint FUN_0003a5c8(int param_1)

{
  if ((int)((uint)*(byte *)(param_1 + 10) << 0x1e) < 0) {
    DAT_2003a474 = 0;
  }
  return (*(byte *)(param_1 + 10) & 3) >> 1;
}

