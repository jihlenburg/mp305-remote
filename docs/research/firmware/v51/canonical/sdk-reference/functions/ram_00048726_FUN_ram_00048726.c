/* Address: ram:00048726; name: FUN_ram_00048726; body bytes: 126 */

undefined4 FUN_ram_00048726(undefined4 *param_1,uint param_2)

{
  uint uVar1;
  
  gp = 0x20004000;
  if (param_2 != 0xf) {
    if (param_2 < 0x10) {
      if (param_2 == 9) goto LAB_ram_000487a0;
      if (param_2 < 10) {
        if (param_2 == 6) {
          return param_1[3];
        }
        if (param_2 == 7) goto LAB_ram_000487a0;
        uVar1 = 5;
      }
      else {
        if (param_2 == 0xd) goto LAB_ram_000487a0;
        if (0xd < param_2) {
          return *param_1;
        }
        uVar1 = 0xb;
      }
    }
    else {
      if (param_2 == 0x17) {
LAB_ram_0004879c:
        return param_1[2];
      }
      if (param_2 < 0x18) {
        if (param_2 == 0x12) goto LAB_ram_000487a0;
        if (param_2 == 0x16) goto LAB_ram_0004879c;
        uVar1 = 0x11;
      }
      else {
        if (param_2 == 0x1d) goto LAB_ram_000487a0;
        if (param_2 < 0x1e) {
          uVar1 = 0x1b;
        }
        else {
          if (param_2 == 0x52) goto LAB_ram_000487a0;
          uVar1 = 0xd2;
        }
      }
    }
    if (param_2 != uVar1) {
      return 0;
    }
  }
LAB_ram_000487a0:
  return param_1[1];
}

