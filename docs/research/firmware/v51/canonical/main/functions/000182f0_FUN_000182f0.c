/* Address: 000182f0; name: FUN_000182f0; body bytes: 96 */

void FUN_000182f0(uint param_1)

{
  if ((param_1 & 1) != 0) {
    DAT_40010400 = 0x3210;
  }
  if ((int)(param_1 << 0x1e) < 0) {
    DAT_40048010 = 0xa5a50001;
  }
  if ((int)(param_1 << 0x1d) < 0) {
    DAT_40053bfc = 0xa501;
  }
  if ((int)(param_1 << 0x1b) < 0) {
    DAT_400543fe = DAT_400543fe | 0xa508;
  }
  if ((int)(param_1 << 0x19) < 0) {
    DAT_400543fe = DAT_400543fe | 0xa503;
  }
  if ((int)(param_1 << 0x18) < 0) {
    DAT_40050804 = 0x77;
    DAT_4005080c = 0x77;
  }
  return;
}

