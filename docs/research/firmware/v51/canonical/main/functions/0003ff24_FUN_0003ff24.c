/* Address: 0003ff24; name: FUN_0003ff24; body bytes: 38 */

uint FUN_0003ff24(uint param_1)

{
  return ((short)(ushort)(byte)(param_1 >> 0x10) * 0x4d + (short)(ushort)(byte)(param_1 >> 8) * 0x97
          + (param_1 & 0xff) * 0x1c & 0xffff) >> 8;
}

