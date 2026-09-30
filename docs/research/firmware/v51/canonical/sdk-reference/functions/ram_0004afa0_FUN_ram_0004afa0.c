/* Address: ram:0004afa0; name: FUN_ram_0004afa0; body bytes: 194 */

int FUN_ram_0004afa0(undefined1 *param_1,undefined4 param_2,uint param_3,undefined2 *param_4)

{
  int iVar1;
  int iVar2;
  ushort auStack_22 [7];
  
  gp = 0x20004000;
  auStack_22[0] = 0;
  iVar2 = 0;
  if (*(short *)(param_1 + 10) != -1) {
    iVar2 = FUN_ram_0004aaf8(*(short *)(param_1 + 10) + 1,param_2,*(undefined4 *)(param_1 + 4),
                             *param_1,auStack_22);
  }
  iVar1 = ATT_CompareUUID(&DAT_ram_0006c65c,2,*(undefined4 *)(param_1 + 4),*param_1);
  if ((iVar1 == 0) &&
     (iVar1 = ATT_CompareUUID(&DAT_ram_0006c660,2,*(undefined4 *)(param_1 + 4),*param_1), iVar1 == 0
     )) {
    iVar1 = ATT_CompareUUID(&DAT_ram_0006c640,2,*(undefined4 *)(param_1 + 4),*param_1);
    if (iVar1 == 0) {
      param_3 = (uint)*(ushort *)(param_1 + 10);
      goto LAB_ram_0004b004;
    }
    if ((iVar2 == 0) || (auStack_22[0] != param_3)) goto LAB_ram_0004aff4;
    param_3 = *(ushort *)(iVar2 + 10) - 1;
  }
  else {
    param_3 = (uint)*(ushort *)(param_1 + 10);
LAB_ram_0004aff4:
    iVar1 = FUN_ram_0004a296(param_3);
    if (iVar1 == 0) goto LAB_ram_0004b004;
    param_3 = (param_3 - 1) + iVar1;
  }
  param_3 = param_3 & 0xffff;
LAB_ram_0004b004:
  if (param_4 != (undefined2 *)0x0) {
    *param_4 = (short)param_3;
  }
  return iVar2;
}

