/* Address: ram:00041b50; name: FUN_ram_00041b50; body bytes: 118 */

void FUN_ram_00041b50(void)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  
  iVar1 = DAT_ram_20001bbc;
  gp = 0x20004000;
  DAT_ram_20001b5c = DAT_ram_20001bbc + 0x220;
  iVar4 = DAT_ram_20001bbc + -8 + (uint)DAT_ram_20001bc0;
  uVar2 = (uint)(DAT_ram_20001bc0 >> 3);
  if (0x1007 < DAT_ram_20001bc0) {
    uVar2 = 0x200;
  }
  piVar3 = (int *)(DAT_ram_20001b5c + uVar2);
  DAT_ram_20001b54 = iVar4;
  DAT_ram_20001b58 = piVar3;
  *(int **)(DAT_ram_20001bbc + 0x220) = piVar3;
  *(short *)(iVar1 + 0x224) = (short)uVar2 + -8;
  *(undefined2 *)(iVar1 + 0x226) = 0;
  *piVar3 = iVar4;
  *(short *)(piVar3 + 1) = ((short)iVar4 - (short)piVar3) + -8;
  *(undefined2 *)((int)piVar3 + 6) = 0;
  DAT_ram_20001b6a = FUN_ram_00041b28();
  return;
}

