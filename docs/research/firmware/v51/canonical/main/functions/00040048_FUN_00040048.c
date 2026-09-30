/* Address: 00040048; name: FUN_00040048; body bytes: 114 */

uint FUN_00040048(byte *param_1,uint param_2,int param_3)

{
  short sVar1;
  short sVar2;
  ushort uVar3;
  
  if (param_3 != 0) {
    if (param_3 == 0xff) {
      uVar3 = (param_1[2] & 0xf8) * 0x100 + (param_1[1] & 0xfc) * 8 + (ushort)(*param_1 >> 3);
    }
    else {
      sVar2 = (short)param_3;
      sVar1 = 0xff - sVar2;
      uVar3 = (((short)(param_2 >> 0xb) * sVar1 + (ushort)(param_1[2] >> 3) * sVar2) * 8 & 0xf800) +
              ((ushort)((uint)((int)(short)(ushort)((param_2 << 0x15) >> 0x1a) * (int)sVar1 +
                              (int)(short)(ushort)(param_1[1] >> 2) * (int)sVar2) >> 3) & 0x7e0) +
              (short)((uint)((int)(short)((ushort)param_2 & 0x1f) * (int)sVar1 +
                            (int)(short)(ushort)(*param_1 >> 3) * (int)sVar2) >> 8);
    }
    return (uint)uVar3;
  }
  return param_2;
}

