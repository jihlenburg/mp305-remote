/* Address: 00036e84; name: FUN_00036e84; body bytes: 30 */

byte FUN_00036e84(int param_1,int param_2)

{
  return *(byte *)(param_1 + ((int)(param_2 + ((uint)(param_2 >> 0x1f) >> 0x1d)) >> 3)) >>
         (7U - param_2 % 8 & 0xff) & 1;
}

