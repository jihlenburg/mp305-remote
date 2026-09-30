/* Address: 000401f4; name: FUN_000401f4; body bytes: 54 */

void FUN_000401f4(uint param_1,byte *param_2,uint param_3)

{
  short sVar1;
  int iVar2;
  
  if (param_3 != 0) {
    if (param_3 < 0xfd) {
      sVar1 = 0xff - (short)param_3;
      iVar2 = (int)(short)param_1 * (int)(short)param_3;
      *param_2 = (byte)((uint)((int)(short)(ushort)*param_2 * (int)sVar1 + iVar2) >> 8);
      param_2[1] = (byte)((uint)((int)(short)(ushort)param_2[1] * (int)sVar1 + iVar2) >> 8);
      param_1 = (uint)((int)(short)(ushort)param_2[2] * (int)sVar1 + iVar2) >> 8;
    }
    else {
      *param_2 = (byte)param_1;
      param_2[1] = (byte)param_1;
    }
    param_2[2] = (byte)param_1;
  }
  return;
}

