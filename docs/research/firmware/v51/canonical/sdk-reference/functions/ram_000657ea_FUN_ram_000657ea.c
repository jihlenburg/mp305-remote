/* Address: ram:000657ea; name: FUN_ram_000657ea; body bytes: 84 */

undefined1 FUN_ram_000657ea(void)

{
  undefined1 auStack_14 [16];
  
  gp = 0x20004000;
  auStack_14[0] = FUN_ram_00066be0();
  thunk_FUN_ram_000521a0(0x2036,2,auStack_14);
  return auStack_14[0];
}

