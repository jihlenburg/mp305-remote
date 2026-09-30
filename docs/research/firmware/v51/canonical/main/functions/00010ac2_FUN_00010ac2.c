/* Address: 00010ac2; name: FUN_00010ac2; body bytes: 38 */

undefined8 FUN_00010ac2(uint param_1)

{
  if ((param_1 & 0x7fffffff) != 0) {
    return CONCAT44(param_1 & 0x80000000 | (((param_1 & 0x7fffffff) >> 0x17) + 0x380) * 0x100000 |
                    (param_1 & 0x7fffff) >> 3,param_1 << 0x1d);
  }
  return 0;
}

