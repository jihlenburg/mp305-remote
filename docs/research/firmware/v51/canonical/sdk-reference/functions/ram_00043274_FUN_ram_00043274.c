/* Address: ram:00043274; name: FUN_ram_00043274; body bytes: 60 */

undefined4 FUN_ram_00043274(int param_1,uint param_2)

{
  uint uVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  if ((param_1 != 0xfffe) && (0x16 < param_2)) {
    uVar1 = FUN_ram_0004c74c();
    if (param_2 <= uVar1) {
      uVar2 = FUN_ram_0004e17a(param_1);
      return uVar2;
    }
    return 1;
  }
  return 1;
}

