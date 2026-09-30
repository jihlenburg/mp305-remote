/* Address: ram:0004e132; name: FUN_ram_0004e132; body bytes: 24 */

undefined1 FUN_ram_0004e132(void)

{
  undefined1 uVar1;
  int iVar2;
  
  gp = 0x20004000;
  iVar2 = FUN_ram_0004df14();
  if (iVar2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined1 *)(iVar2 + 0xc);
  }
  return uVar1;
}

