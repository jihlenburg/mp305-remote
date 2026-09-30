/* Address: ram:00055afc; name: FUN_ram_00055afc; body bytes: 90 */

/* WARNING: Removing unreachable block (ram,0x00055b22) */
/* WARNING: Removing unreachable block (ram,0x00055b14) */

void FUN_ram_00055afc(int param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  gp = 0x20004000;
  uVar3 = (uint)*(ushort *)(param_1 + 0x1ca);
  if (*(char *)(param_1 + 0x146) == '\x02') {
    if (*(short *)(param_1 + 0x148) == 0) {
      iVar1 = 8;
      iVar4 = (int)(uVar3 - 0x178) / 8 + -0x2b;
      goto LAB_ram_00055b2a;
    }
    iVar4 = (int)(uVar3 - 0x178) / 2 + -0x2b;
  }
  else {
    if (*(char *)(param_1 + 0x146) == '\x01') {
      iVar4 = uVar3 - 0x44;
      iVar1 = 4;
      goto LAB_ram_00055b2a;
    }
    iVar4 = uVar3 - 0x50;
  }
  iVar1 = 8;
LAB_ram_00055b2a:
  if (iVar1 == 0) {
    uVar3 = 0xffffffff;
  }
  else {
    uVar3 = iVar4 / iVar1;
  }
  uVar2 = (uint)*(ushort *)(param_1 + 0x1c8);
  if ((uVar3 & 0xffff) < (uint)*(ushort *)(param_1 + 0x1c8)) {
    uVar2 = uVar3 & 0xffff;
  }
  *(char *)(param_1 + 0x4c) = (char)uVar2;
  return;
}

