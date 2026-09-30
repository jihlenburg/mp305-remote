/* Address: ram:00041b28; name: FUN_ram_00041b28; body bytes: 40 */

int FUN_ram_00041b28(void)

{
  int iVar1;
  int *piVar2;
  
  gp = 0x20004000;
  iVar1 = 0;
  for (piVar2 = (int *)DAT_ram_20001b5c; (int *)DAT_ram_20001b54 != piVar2; piVar2 = (int *)*piVar2)
  {
    if (*(short *)((int)piVar2 + 6) == 0) {
      iVar1 = iVar1 + (uint)*(ushort *)(piVar2 + 1);
    }
  }
  return iVar1;
}

