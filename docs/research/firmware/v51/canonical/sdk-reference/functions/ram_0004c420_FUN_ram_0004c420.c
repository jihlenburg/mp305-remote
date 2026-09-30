/* Address: ram:0004c420; name: FUN_ram_0004c420; body bytes: 78 */

void FUN_ram_0004c420(int param_1)

{
  int iVar1;
  
  gp = 0x20004000;
  iVar1 = *(int *)(param_1 + 0xc);
  if (iVar1 != 0) {
    if (*(int *)(iVar1 + 0xc) != 0) {
      FUN_ram_20000104();
    }
    if (*(int *)(iVar1 + 0x14) != 0) {
      FUN_ram_20000104();
    }
    FUN_ram_20000104(iVar1);
  }
  tmos_memset(param_1,0,0x10);
  *(undefined1 *)(param_1 + 9) = 0xff;
  return;
}

