/* Address: ram:000657a4; name: FUN_ram_000657a4; body bytes: 38 */

undefined1 FUN_ram_000657a4(void)

{
  undefined1 auStack_11 [13];
  
  gp = 0x20004000;
  auStack_11[0] = FUN_ram_00066b28();
  thunk_FUN_ram_000521a0(0x2031,1,auStack_11);
  return auStack_11[0];
}

