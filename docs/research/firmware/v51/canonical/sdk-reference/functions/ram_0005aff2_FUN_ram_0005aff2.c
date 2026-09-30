/* Address: ram:0005aff2; name: FUN_ram_0005aff2; body bytes: 46 */

undefined4 FUN_ram_0005aff2(int param_1)

{
  int iVar1;
  
  gp = 0x20004000;
  *(undefined1 *)(param_1 + 0x15) = 2;
  iVar1 = *(int *)(param_1 + 0x110);
  *(undefined1 *)(iVar1 + 2) = 0x1e;
  *(undefined1 *)(iVar1 + 3) = *(undefined1 *)(param_1 + 0x2e);
  *(uint *)(param_1 + 0xa0) = *(uint *)(param_1 + 0xa0) | 0x8000;
  *(undefined1 *)(param_1 + 0x10) = 1;
  return 0;
}

