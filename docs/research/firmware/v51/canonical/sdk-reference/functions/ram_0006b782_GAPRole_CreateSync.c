/* Address: ram:0006b782; name: GAPRole_CreateSync; body bytes: 52 */

void GAPRole_CreateSync(int param_1)

{
  undefined1 auStack_20 [2];
  undefined1 uStack_1e;
  
  gp = 0x20004000;
  tmos_memcpy(auStack_20,param_1,0x10);
  uStack_1e = FUN_ram_000442de(*(undefined1 *)(param_1 + 2),param_1 + 3);
  thunk_FUN_ram_00067d78(auStack_20);
  return;
}

