/* Address: ram:0004e066; name: FUN_ram_0004e066; body bytes: 24 */

undefined2 FUN_ram_0004e066(void)

{
  undefined2 uVar1;
  int iVar2;
  
  gp = 0x20004000;
  iVar2 = FUN_ram_0004df14();
  if (iVar2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined2 *)(iVar2 + 0x14);
  }
  return uVar1;
}

