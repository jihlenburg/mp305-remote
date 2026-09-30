/* Address: ram:00055958; name: FUN_ram_00055958; body bytes: 30 */

int FUN_ram_00055958(uint param_1)

{
  int iVar1;
  
  gp = 0x20004000;
  for (iVar1 = *(int *)(DAT_ram_20001db0 + 0x28);
      (iVar1 != 0 && (*(ushort *)(iVar1 + 0x18) != param_1)); iVar1 = iVar1 + 0x58) {
  }
  return iVar1;
}

