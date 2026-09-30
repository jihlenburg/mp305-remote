/* Address: ram:00055d70; name: FUN_ram_00055d70; body bytes: 46 */

void FUN_ram_00055d70(int param_1)

{
  undefined2 uVar1;
  int iVar2;
  
  gp = 0x20004000;
  iVar2 = (uint)*(ushort *)(param_1 + 0x48) * 5;
  if ((uint)*(ushort *)(param_1 + 0x3c) < (uint)(iVar2 >> 3)) {
    iVar2 = ((uint)*(ushort *)(param_1 + 0x48) - (uint)*(ushort *)(param_1 + 0x3c)) * 8;
  }
  if (*(ushort *)(param_1 + 0x38) == 0) {
    uVar1 = 0xffff;
  }
  else {
    uVar1 = (undefined2)(iVar2 / (int)(uint)*(ushort *)(param_1 + 0x38));
  }
  *(undefined2 *)(param_1 + 0x46) = uVar1;
  return;
}

