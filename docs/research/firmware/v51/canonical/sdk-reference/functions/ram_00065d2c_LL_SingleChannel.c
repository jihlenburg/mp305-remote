/* Address: ram:00065d2c; name: LL_SingleChannel; body bytes: 156 */

undefined4 LL_SingleChannel(uint param_1)

{
  int iVar1;
  
  iVar1 = DAT_ram_20001efc;
  gp = 0x20004000;
  if (param_1 == 0) {
    param_1 = 0x25;
    goto LAB_ram_00065d3e;
  }
  if (param_1 < 0xc) {
    param_1 = param_1 - 1;
  }
  else {
    if (param_1 == 0xc) {
      param_1 = 0x26;
      goto LAB_ram_00065d3e;
    }
    if (0x26 < param_1) {
      if (param_1 != 0x27) {
        return 0x12;
      }
      goto LAB_ram_00065d3e;
    }
    param_1 = param_1 - 2;
  }
  param_1 = param_1 & 0xff;
LAB_ram_00065d3e:
  *(uint *)(DAT_ram_20001efc + 0x10) =
       (param_1 & 0x3f) << 0x18 | *(uint *)(DAT_ram_20001efc + 0x10) & 0xc0ffffff;
  *(uint *)(iVar1 + 0x10) = *(uint *)(iVar1 + 0x10) & 0xffffc0ff | (DAT_ram_20001bd0 & 0x3f) << 8;
  *(uint *)(iVar1 + 0x5c) = *(uint *)(iVar1 + 0x5c) | 4;
  *(uint *)(iVar1 + 0x10) = *(uint *)(iVar1 + 0x10) & 0xfff8ffff | 0x20000;
  *(undefined4 *)(iVar1 + 8) = 0x204f8;
  return 0;
}

