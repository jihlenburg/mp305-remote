/* Address: ram:00066694; name: FUN_ram_00066694; body bytes: 54 */

undefined4 FUN_ram_00066694(int param_1)

{
  int iVar1;
  undefined1 uVar2;
  
  gp = 0x20004000;
  iVar1 = 0;
  do {
    uVar2 = FUN_ram_000428ec(1,0xff);
    *(undefined1 *)(param_1 + iVar1) = uVar2;
    iVar1 = iVar1 + 1;
  } while (iVar1 != 8);
  return 0;
}

