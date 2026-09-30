/* Address: ram:2000082c; name: FUN_ram_2000082c; body bytes: 1 */

bool FUN_ram_2000082c(int param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int *piVar5;
  uint uVar6;
  
  gp = 0x20004000;
  if ((*(byte *)(param_1 + 0x18) & 0xfe) != 0) {
    gp = 0x20004000;
    return false;
  }
  if (*(char *)(param_1 + 0x19) != '\0') {
    gp = 0x20004000;
    return false;
  }
  if ((*(char *)(param_1 + 0x12) == '\0') || (DAT_ram_20001bcf <= *(byte *)(param_1 + 0x34))) {
    if ((*(byte *)(param_1 + 0xc) & 0x10) == 0) {
      gp = 0x20004000;
      return false;
    }
    uVar4 = 0;
    if (*(char *)(param_1 + 0x12) != '\0') goto code_r0x20000860;
  }
  else {
code_r0x20000860:
    uVar4 = (uint)*(ushort *)(param_1 + 0x1c6);
    if ((*(byte *)(param_1 + 0xc) & 0x10) == 0) goto code_r0x2000086e;
  }
  uVar4 = uVar4 + *(ushort *)(param_1 + 0x1ca);
code_r0x2000086e:
  if (uVar4 == 0) {
    return false;
  }
  uVar1 = 0xffffffff;
  iVar2 = FUN_ram_0006bae2((uVar4 + 300) * (uint)DAT_ram_20001b8c,
                           (int)((ulonglong)(uVar4 + 300) * (ulonglong)(uint)DAT_ram_20001b8c >>
                                0x20),1000000,0);
  uVar4 = (uint)DAT_ram_20001bd5;
  piVar5 = DAT_ram_20001df0;
  do {
    if ((uint)piVar5[0x24] < uVar1) {
      uVar1 = piVar5[0x24];
    }
    piVar5 = (int *)*piVar5;
  } while (piVar5 != (int *)0x0);
  uVar3 = (*DAT_ram_20001c00)();
  uVar6 = 0;
  if (uVar3 <= uVar1) {
    uVar6 = uVar1 - uVar3;
  }
  return uVar4 + iVar2 <= uVar6;
}

