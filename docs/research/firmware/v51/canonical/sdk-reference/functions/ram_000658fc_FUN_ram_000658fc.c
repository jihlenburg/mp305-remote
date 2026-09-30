/* Address: ram:000658fc; name: FUN_ram_000658fc; body bytes: 38 */

undefined1 FUN_ram_000658fc(void)

{
  undefined1 auStack_11 [13];
  
  gp = 0x20004000;
  auStack_11[0] = FUN_ram_00067596();
  thunk_FUN_ram_000521a0(0x2040,1,auStack_11);
  return auStack_11[0];
}

