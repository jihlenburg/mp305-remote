/* Address: 0003fe7c; name: FUN_0003fe7c; body bytes: 46 */

uint FUN_0003fe7c(ushort param_1)

{
  return ((param_1 & 0x1f) * 0xe7 +
          (uint)(param_1 >> 0xb) * 0x27b + (short)(ushort)(((uint)param_1 << 0x15) >> 0x1a) * 0x265
         & 0xffff) >> 8;
}

