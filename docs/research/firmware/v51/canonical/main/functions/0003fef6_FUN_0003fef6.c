/* Address: 0003fef6; name: FUN_0003fef6; body bytes: 34 */

uint FUN_0003fef6(byte *param_1)

{
  return ((short)(ushort)param_1[2] * 0x4d + (short)(ushort)param_1[1] * 0x97 +
          (uint)*param_1 * 0x1c & 0xffff) >> 8;
}

