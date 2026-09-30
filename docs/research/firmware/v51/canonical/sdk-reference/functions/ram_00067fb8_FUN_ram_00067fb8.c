/* Address: ram:00067fb8; name: FUN_ram_00067fb8; body bytes: 22 */

undefined4 FUN_ram_00067fb8(void)

{
  undefined4 uVar1;
  uint in_a5;
  
  gp = 0x20004000;
  uVar1 = 0;
  if (((int)(uint)DAT_ram_20001daa >> (in_a5 & 0x1f) & 1U) == 0) {
    uVar1 = 0x11;
  }
  return uVar1;
}

