/* Address: ram:00048f06; name: FUN_ram_00048f06; body bytes: 192 */

undefined4 FUN_ram_00048f06(undefined2 *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined1 auStack_14 [8];
  
  gp = 0x20004000;
  if (param_2 == 0x17) {
    iVar1 = ATT_GetMTU(*param_1);
    uVar4 = (uint)(ushort)param_1[10];
    uVar2 = ((ushort)param_1[0xe] - 5) + iVar1;
    uVar3 = uVar2 & 0xffff;
    param_1[0xe] = (short)(uVar2 * 0x10000 >> 0x10);
    uVar2 = uVar3 - (ushort)param_1[9] & 0xffff;
    if (uVar4 <= uVar2) {
      auStack_14[0] = 1;
      goto LAB_ram_00048f8e;
    }
    if ((int)(uVar4 - uVar2) < iVar1 + -4) {
      uVar4 = ((ushort)param_1[9] + uVar4) - uVar3;
    }
    else {
      uVar4 = iVar1 - 5;
    }
    iVar1 = FUN_ram_00048dc4(*param_1,param_1[8],uVar3,uVar4 & 0xffff,
                             *(int *)(param_1 + 0xc) + uVar2);
    if (iVar1 == 0) {
      FUN_ram_00042194(*(undefined1 *)(param_1 + 4),48000);
      gp = 0x20004000;
      return 0x16;
    }
  }
  auStack_14[0] = 0;
LAB_ram_00048f8e:
  FUN_ram_000438e4(*param_1,auStack_14);
  if (param_2 != 1) {
    FUN_ram_00042194(*(undefined1 *)(param_1 + 4),48000);
    *(undefined1 *)(param_1 + 1) = 0x19;
    *(undefined1 **)(param_1 + 2) = &LAB_ram_000438da;
    return 0x16;
  }
  gp = 0x20004000;
  return 1;
}

