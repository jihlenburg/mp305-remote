/* Address: ram:0005b18e; name: FUN_ram_0005b18e; body bytes: 56 */

undefined4 FUN_ram_0005b18e(int param_1)

{
  int iVar1;
  
  gp = 0x20004000;
  *(undefined1 *)(param_1 + 0x15) = 4;
  iVar1 = *(int *)(param_1 + 0x110);
  *(undefined1 *)(iVar1 + 2) = 0x28;
  *(undefined1 *)(iVar1 + 3) = DAT_ram_20001dac;
  *(undefined1 *)(iVar1 + 4) = 10;
  *(undefined1 *)(iVar1 + 5) = 0x32;
  *(undefined1 *)(param_1 + 0x10) = 0x95;
  return 0;
}

