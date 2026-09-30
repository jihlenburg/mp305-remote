/* Address: 000400ba; name: FUN_000400ba; body bytes: 76 */

void FUN_000400ba(byte *param_1,byte *param_2,uint param_3)

{
  short sVar1;
  short sVar2;
  byte bVar3;
  
  if (param_3 != 0) {
    if (param_3 < 0xfd) {
      sVar2 = (short)param_3;
      sVar1 = 0xff - sVar2;
      *param_2 = (byte)((uint)((int)(short)(ushort)*param_2 * (int)sVar1 +
                              (int)(short)(ushort)*param_1 * (int)sVar2) >> 8);
      param_2[1] = (byte)((uint)((int)(short)(ushort)param_2[1] * (int)sVar1 +
                                (int)(short)(ushort)param_1[1] * (int)sVar2) >> 8);
      bVar3 = (byte)((uint)((int)(short)(ushort)param_2[2] * (int)sVar1 +
                           (int)(short)(ushort)param_1[2] * (int)sVar2) >> 8);
    }
    else {
      *param_2 = *param_1;
      param_2[1] = param_1[1];
      bVar3 = param_1[2];
    }
    param_2[2] = bVar3;
  }
  return;
}

