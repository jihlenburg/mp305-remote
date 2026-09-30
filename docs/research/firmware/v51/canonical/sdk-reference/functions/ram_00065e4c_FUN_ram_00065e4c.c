/* Address: ram:00065e4c; name: FUN_ram_00065e4c; body bytes: 36 */

undefined4 FUN_ram_00065e4c(int param_1)

{
  undefined1 *puVar1;
  int iVar2;
  undefined1 *puVar3;
  
  gp = 0x20004000;
  puVar3 = &DAT_ram_20001d60;
  iVar2 = 0;
  do {
    puVar1 = (undefined1 *)(param_1 + iVar2);
    iVar2 = iVar2 + 1;
    *puVar1 = puVar3[0xd8];
    puVar3 = puVar3 + 1;
  } while (iVar2 != 6);
  return 0;
}

