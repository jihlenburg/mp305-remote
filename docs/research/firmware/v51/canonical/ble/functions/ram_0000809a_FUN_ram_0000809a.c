/* Address: ram:0000809a; name: FUN_ram_0000809a; body bytes: 108 */

uint FUN_ram_0000809a(int param_1,code *param_2)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  gp = &DAT_ram_20002000;
  uVar4 = 0;
  for (piVar1 = (int *)(param_1 + 0x48); piVar1 != (int *)0x0; piVar1 = (int *)*piVar1) {
    iVar2 = piVar1[2];
    iVar5 = piVar1[1];
    while (iVar5 = iVar5 + -1, -1 < iVar5) {
      if ((1 < *(ushort *)(iVar2 + 0xc)) && (*(short *)(iVar2 + 0xe) != -1)) {
        uVar3 = (*param_2)(param_1,iVar2);
        uVar4 = uVar4 | uVar3;
      }
      iVar2 = iVar2 + 0x68;
    }
  }
  return uVar4;
}

