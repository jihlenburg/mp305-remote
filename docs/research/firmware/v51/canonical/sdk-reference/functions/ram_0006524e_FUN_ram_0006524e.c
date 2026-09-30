/* Address: ram:0006524e; name: FUN_ram_0006524e; body bytes: 36 */

undefined1 FUN_ram_0006524e(void)

{
  undefined1 auStack_11 [13];
  
  gp = 0x20004000;
  auStack_11[0] = FUN_ram_00065f68();
  thunk_FUN_ram_000521a0(0x200a,1,auStack_11);
  return auStack_11[0];
}

