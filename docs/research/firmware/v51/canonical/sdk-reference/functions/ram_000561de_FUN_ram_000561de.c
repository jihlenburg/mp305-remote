/* Address: ram:000561de; name: FUN_ram_000561de; body bytes: 246 */

void FUN_ram_000561de(int param_1)

{
  undefined2 uVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  
  gp = 0x20004000;
  piVar4 = DAT_ram_20001df0;
  if (DAT_ram_20001e04 < 2) {
    *(undefined1 *)(param_1 + 0x1c) = 0;
    return;
  }
  for (; piVar3 = DAT_ram_20001df0, piVar4 != (int *)0x0; piVar4 = (int *)*piVar4) {
    if (*(char *)((int)piVar4 + 0x1d) != '\0') {
      gp = 0x20004000;
      return;
    }
  }
  while( true ) {
    if ((piVar3 == (int *)0x0) ||
       ((piVar3 == (int *)param_1 && (piVar3 = (int *)*piVar3, piVar3 == (int *)0x0)))) {
      *(undefined1 *)(param_1 + 0x1c) = 0;
      return;
    }
    if ((*(char *)((int)piVar3 + 0xb) == '\0') && (piVar3[0x23] != *(int *)(param_1 + 0x8c))) break;
    piVar3 = (int *)*piVar3;
  }
  if (*(char *)(param_1 + 0x1c) == -0x80) {
    iVar2 = piVar3[0xe];
    *(short *)(param_1 + 0x72) = (short)iVar2;
    *(short *)(param_1 + 0x74) = (short)iVar2;
    *(undefined2 *)(param_1 + 0x58) = *(undefined2 *)((int)piVar3 + 0x3a);
    *(short *)(param_1 + 0x5a) = (short)piVar3[0xf];
    FUN_ram_0005d5f6(*(undefined2 *)(param_1 + 8),0x80,6);
    *(undefined1 *)(param_1 + 0x1d) = 1;
    *(byte *)(param_1 + 0x1c) = *(byte *)(param_1 + 0x1c) & 0x7f;
  }
  else {
    uVar1 = *(undefined2 *)(param_1 + 0x38);
    *(undefined2 *)((int)piVar3 + 0x72) = uVar1;
    *(undefined2 *)(piVar3 + 0x1d) = uVar1;
    *(undefined2 *)(piVar3 + 0x16) = *(undefined2 *)(param_1 + 0x3a);
    *(undefined2 *)((int)piVar3 + 0x5a) = *(undefined2 *)(param_1 + 0x3c);
    FUN_ram_0005d5f6((short)piVar3[2],0x80,6);
    *(undefined1 *)((int)piVar3 + 0x1d) = 2;
  }
  tmos_memset((int)piVar3 + 0x66,0xff,0xc);
  return;
}

