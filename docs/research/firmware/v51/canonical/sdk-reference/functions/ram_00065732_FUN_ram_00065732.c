/* Address: ram:00065732; name: FUN_ram_00065732; body bytes: 38 */

undefined1 FUN_ram_00065732(void)

{
  undefined1 auStack_11 [13];
  
  gp = 0x20004000;
  auStack_11[0] = FUN_ram_00066a3e();
  thunk_FUN_ram_000521a0(0x2029,1,auStack_11);
  return auStack_11[0];
}

