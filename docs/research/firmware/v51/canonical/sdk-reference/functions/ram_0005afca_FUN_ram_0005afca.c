/* Address: ram:0005afca; name: FUN_ram_0005afca; body bytes: 40 */

undefined4 FUN_ram_0005afca(int param_1)

{
  int iVar1;
  
  gp = 0x20004000;
  *(undefined1 *)(param_1 + 0x15) = 2;
  iVar1 = *(int *)(param_1 + 0x110);
  *(undefined1 *)(iVar1 + 2) = 0x1d;
  *(undefined1 *)(iVar1 + 3) = DAT_ram_20001d63;
  *(undefined1 *)(param_1 + 0x10) = 0x75;
  return 0;
}

