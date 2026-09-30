/* Address: ram:0004ebc6; name: FUN_ram_0004ebc6; body bytes: 28 */

undefined4 FUN_ram_0004ebc6(int param_1,byte *param_2)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  uVar1 = 2;
  if ((param_1 != 0) && (param_2 != (byte *)0x0)) {
    uVar1 = 0x18;
    if (*(byte *)(param_1 + 1) < 0x10) {
      *param_2 = *(byte *)(param_1 + 1);
      uVar1 = 0;
    }
  }
  return uVar1;
}

