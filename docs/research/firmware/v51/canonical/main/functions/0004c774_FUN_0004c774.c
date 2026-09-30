/* Address: 0004c774; name: FUN_0004c774; body bytes: 84 */

uint FUN_0004c774(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = FUN_0004c768();
  if (2 < uVar1) {
    uVar2 = 0xff;
    if (uVar1 < 0xfd) {
      uVar2 = uVar1 * 0xff >> 8;
    }
    if (param_2 == 0) goto LAB_0004c794;
    param_2 = 0;
    for (; param_1 != 0; param_1 = FUN_0004bc8c(param_1)) {
      uVar1 = FUN_0004c768(param_1,param_2);
      if (uVar1 < 3) {
        return 0;
      }
      if (uVar1 < 0xfd) {
        uVar2 = uVar1 * uVar2 >> 8;
      }
LAB_0004c794:
    }
    if (2 < uVar2) {
      if (uVar2 < 0xfd) {
        return uVar2;
      }
      return 0xff;
    }
  }
  return 0;
}

