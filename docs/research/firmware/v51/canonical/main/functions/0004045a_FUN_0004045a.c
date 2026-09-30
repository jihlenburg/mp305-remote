/* Address: 0004045a; name: FUN_0004045a; body bytes: 96 */

uint FUN_0004045a(uint param_1,uint param_2)

{
  short sVar1;
  byte bVar2;
  
  if (0xfc < param_1 >> 0x18) {
    return param_1 & 0xffffff | param_2 & 0xff000000;
  }
  if (param_1 >> 0x18 < 3) {
    return param_2;
  }
  bVar2 = (byte)(param_1 >> 0x18);
  sVar1 = 0xff - (ushort)bVar2;
  return param_2 & 0xff000000 |
         ((uint)((int)(short)(ushort)(byte)(param_2 >> 0x10) * (int)sVar1 +
                (int)(short)(ushort)(byte)(param_1 >> 0x10) * (int)(short)(ushort)bVar2) >> 8 & 0xff
         ) << 0x10 |
         ((uint)((int)(short)(ushort)(byte)(param_2 >> 8) * (int)sVar1 +
                (int)(short)(ushort)(byte)(param_1 >> 8) * (int)(short)(ushort)bVar2) >> 8 & 0xff)
         << 8 | (uint)((int)(short)((ushort)param_2 & 0xff) * (int)sVar1 +
                      (int)(short)((ushort)param_1 & 0xff) * (int)(short)(ushort)bVar2) >> 8 & 0xff;
}

