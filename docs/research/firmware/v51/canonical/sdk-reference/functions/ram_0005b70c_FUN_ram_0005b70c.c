/* Address: ram:0005b70c; name: FUN_ram_0005b70c; body bytes: 82 */

undefined4 FUN_ram_0005b70c(int param_1)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  
  gp = 0x20004000;
  *(undefined1 *)(param_1 + 0x15) = 1;
  bVar1 = *(byte *)(param_1 + 0x153);
  iVar3 = *(int *)(param_1 + 0x110);
  cVar2 = *(char *)(param_1 + 0x154);
  *(byte *)(iVar3 + 2) = cVar2 << 6 | bVar1;
  *(undefined1 *)(iVar3 + 3) = 0x1b;
  *(byte *)(param_1 + 0xc) = *(byte *)(param_1 + 0xc) | 0x20;
  FUN_ram_00062148(cVar2,bVar1,*(undefined1 *)(param_1 + 0x152),1);
  *(undefined1 *)(param_1 + 0x10) = 0x67;
  return 0;
}

