/* Address: 0003ff4c; name: FUN_0003ff4c; body bytes: 54 */

uint FUN_0003ff4c(uint param_1,uint param_2,int param_3)

{
  uint uVar1;
  
  if (param_3 != 0xff) {
    if (param_3 == 0) {
      return param_2;
    }
    if (param_1 != param_2) {
      uVar1 = (param_2 | param_2 << 0x10) & 0x7e0f81f;
      uVar1 = uVar1 + ((param_3 + 4U >> 3) * (((param_1 | param_1 << 0x10) & 0x7e0f81f) - uVar1) >>
                      5);
      param_1 = uVar1 & 0xf81f | (uVar1 & 0x7e0f81f) >> 0x10;
    }
  }
  return param_1;
}

