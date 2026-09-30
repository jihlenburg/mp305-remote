/* Address: ram:00041bc6; name: FUN_ram_00041bc6; body bytes: 44 */

void FUN_ram_00041bc6(void)

{
  ushort uVar1;
  int *piVar2;
  
  gp = 0x20004000;
  uVar1 = 0;
  for (piVar2 = (int *)DAT_ram_20001b5c; (int *)DAT_ram_20001b54 != piVar2; piVar2 = (int *)*piVar2)
  {
    if ((*(short *)((int)piVar2 + 6) == 0) && (uVar1 < *(ushort *)(piVar2 + 1))) {
      uVar1 = *(ushort *)(piVar2 + 1);
    }
  }
  return;
}

