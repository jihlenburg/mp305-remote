/* Address: ram:0005b22c; name: FUN_ram_0005b22c; body bytes: 88 */

bool FUN_ram_0005b22c(int param_1)

{
  int iVar1;
  
  gp = 0x20004000;
  iVar1 = *(int *)(param_1 + 0x110);
  *(undefined1 *)(param_1 + 0x15) = 0xd;
  if (iVar1 != 0) {
    *(undefined1 *)(iVar1 + 2) = 4;
    tmos_memcpy(iVar1 + 3,param_1 + 0x1a8,8);
    tmos_memcpy(iVar1 + 0xb,param_1 + 0x1b0,4);
    *(undefined1 *)(param_1 + 0x10) = 0x22;
  }
  return iVar1 == 0;
}

