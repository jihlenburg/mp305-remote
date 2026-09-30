/* Address: 0003feaa; name: FUN_0003feaa; body bytes: 60 */

void FUN_0003feaa(ushort *param_1,int param_2)

{
  ushort uVar1;
  short sVar2;
  
  if (param_2 != 0xff) {
    if (param_2 == 0) {
      FUN_0004a57a(param_1,0,2);
      return;
    }
    uVar1 = *param_1;
    sVar2 = (short)param_2;
    *param_1 = (ushort)(((uint)((int)(short)(uVar1 >> 0xb) * (int)sVar2) >> 8 & 0x1f) << 0xb) |
               (ushort)(((uint)((int)(short)(ushort)(((uint)uVar1 << 0x15) >> 0x1a) * (int)sVar2) >>
                         8 & 0x3f) << 5) |
               (ushort)((uint)((int)(short)(uVar1 & 0x1f) * (int)sVar2) >> 8) & 0x1f;
  }
  return;
}

