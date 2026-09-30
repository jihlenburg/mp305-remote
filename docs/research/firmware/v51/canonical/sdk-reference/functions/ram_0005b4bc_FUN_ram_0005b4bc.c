/* Address: ram:0005b4bc; name: FUN_ram_0005b4bc; body bytes: 48 */

undefined4 FUN_ram_0005b4bc(int param_1)

{
  int iVar1;
  
  gp = 0x20004000;
  *(undefined1 *)(param_1 + 0x15) = 0xb;
  iVar1 = *(int *)(param_1 + 0x110);
  *(undefined1 *)(iVar1 + 2) = 0x29;
  tmos_memcpy(iVar1 + 3,param_1 + 0x17d,10);
  return 0;
}

