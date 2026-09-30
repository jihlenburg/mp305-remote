/* Address: ram:0006b7ea; name: GAPRole_UpdatePHY; body bytes: 4 */

undefined4 GAPRole_UpdatePHY(void)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  uVar1 = FUN_ram_00066b68();
  thunk_FUN_ram_00052202(uVar1,0x2032);
  return uVar1;
}

