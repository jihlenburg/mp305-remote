/* Address: 00040280; name: FUN_00040280; body bytes: 28 */

void FUN_00040280(uint param_1,byte *param_2,uint param_3)

{
  if (param_3 != 0) {
    if (param_3 < 0xfd) {
      param_1 = (uint)((int)(short)(ushort)*param_2 * (int)(short)(0xff - (short)param_3) +
                      (int)(short)param_1 * (int)(short)param_3) >> 8;
    }
    *param_2 = (byte)param_1;
  }
  return;
}

