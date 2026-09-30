/* Address: 0004050c; name: FUN_0004050c; body bytes: 48 */

void FUN_0004050c(byte *param_1)

{
  byte bVar1;
  
  bVar1 = param_1[3];
  if (bVar1 != 0xff) {
    if (bVar1 == 0) {
      FUN_0004a57a(param_1,0,4);
      return;
    }
    param_1[2] = (byte)((uint)((int)(short)(ushort)param_1[2] * (int)(short)(ushort)bVar1) >> 8);
    param_1[1] = (byte)((uint)((int)(short)(ushort)param_1[1] * (int)(short)(ushort)bVar1) >> 8);
    *param_1 = (byte)((uint)((int)(short)(ushort)*param_1 * (int)(short)(ushort)bVar1) >> 8);
  }
  return;
}

