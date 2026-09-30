/* Address: ram:0004e0e6; name: FUN_ram_0004e0e6; body bytes: 76 */

undefined4 FUN_ram_0004e0e6(void)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_0004df14();
  if (iVar1 == 0) {
    uVar2 = 2;
  }
  else {
    FUN_ram_0004de30(*(undefined2 *)(iVar1 + 2),1);
    if (*(int *)(iVar1 + 0x2c) != 0) {
      FUN_ram_20000104();
    }
    tmos_memset(iVar1,0,0x3c);
    *(undefined2 *)(iVar1 + 2) = 0xffff;
    *(undefined1 *)(iVar1 + 4) = 0;
    uVar2 = 0;
  }
  return uVar2;
}

