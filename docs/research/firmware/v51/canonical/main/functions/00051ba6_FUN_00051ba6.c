/* Address: 00051ba6; name: FUN_00051ba6; body bytes: 130 */

uint FUN_00051ba6(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  if (0x7f < param_1) {
    uVar1 = param_1 & 0x3f | 0x80;
    if (param_1 < 0x800) {
      param_1 = (param_1 & 0x7ff) >> 6 | 0xc0 | uVar1 << 8;
    }
    else {
      uVar2 = (param_1 & 0xfff) >> 6;
      if (0xffff < param_1) {
        if (0x10ffff < param_1) {
          return 0;
        }
        return (param_1 & 0x1fffff) >> 0x12 | 0xf0 | ((param_1 & 0x3ffff) >> 0xc | 0x80) << 8 |
               (uVar2 | 0x80) << 0x10 | uVar1 << 0x18;
      }
      param_1 = (param_1 & 0xffff) >> 0xc | 0xe0 | (uVar2 | 0x80) << 8 | uVar1 << 0x10;
    }
  }
  return param_1;
}

