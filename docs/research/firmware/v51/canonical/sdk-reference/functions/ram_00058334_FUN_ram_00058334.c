/* Address: ram:00058334; name: FUN_ram_00058334; body bytes: 84 */

void FUN_ram_00058334(int param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  gp = 0x20004000;
  uVar3 = *(undefined4 *)(param_1 + 0x138);
  uVar4 = *(undefined4 *)(param_1 + 0x13c);
  *(undefined1 *)(param_1 + 0x137) = 0;
  *(undefined1 *)(param_1 + 0x12d) = 0;
  iVar1 = 0;
  do {
    uVar2 = FUN_ram_0006ba8a(uVar3,uVar4,iVar1);
    if ((uVar2 & 1) != 0) {
      *(char *)(param_1 + 0x12d) = *(char *)(param_1 + 0x12d) + '\x01';
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 != 0x25);
  return;
}

