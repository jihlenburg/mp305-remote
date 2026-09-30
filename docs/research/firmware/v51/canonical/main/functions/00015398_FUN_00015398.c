/* Address: 00015398; name: FUN_00015398; body bytes: 22 */

void FUN_00015398(ushort param_1,int param_2)

{
  if (param_2 == 1) {
    DAT_40053bf4 = DAT_40053bf4 | param_1 & 0x1f;
  }
  else {
    DAT_40053bf4 = DAT_40053bf4 & ~(param_1 & 0x1f);
  }
  return;
}

