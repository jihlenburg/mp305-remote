/* Address: 00040194; name: FUN_00040194; body bytes: 96 */

uint FUN_00040194(uint param_1,uint param_2,int param_3)

{
  short sVar1;
  short sVar2;
  ushort uVar3;
  int iVar4;
  
  if (param_3 != 0) {
    if (param_3 == 0xff) {
      uVar3 = ((ushort)param_1 & 0xf8) * 0x100 + (short)((param_1 & 0xfc) << 3) +
              (short)(param_1 >> 3);
    }
    else {
      sVar2 = (short)param_3;
      sVar1 = 0xff - sVar2;
      iVar4 = (int)(short)(param_1 >> 3) * (int)sVar2;
      uVar3 = ((ushort)((uint)((int)(short)(ushort)((param_2 << 0x15) >> 0x1a) * (int)sVar1 +
                              (int)(short)(param_1 >> 2) * (int)sVar2) >> 3) & 0x7e0) +
              (((short)(param_2 >> 0xb) * sVar1 + (short)iVar4) * 8 & 0xf800U) +
              (short)((uint)((int)(short)((ushort)param_2 & 0x1f) * (int)sVar1 + iVar4) >> 8);
    }
    return (uint)uVar3;
  }
  return param_2;
}

