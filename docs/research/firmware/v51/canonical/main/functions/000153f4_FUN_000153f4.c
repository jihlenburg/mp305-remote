/* Address: 000153f4; name: FUN_000153f4; body bytes: 18 */

void FUN_000153f4(ushort param_1)

{
  DAT_40053bf8 = DAT_40053bf8 & 0x8fff | param_1 & 0x7000;
  return;
}

