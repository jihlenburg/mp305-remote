/* Address: 00051db8; name: FUN_00051db8; body bytes: 246 */

undefined8 FUN_00051db8(int param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  int local_30;
  int iStack_2c;
  int local_28;
  int local_24;
  
  if ((-1 < (int)((uint)*(byte *)(param_1 + 0x70) << 0x1c)) ||
     ((local_30 = param_1, iStack_2c = param_2, param_2 != 10 && (param_2 != 0xd)))) {
    iStack_2c = 0;
    local_30 = param_2;
    local_28 = param_3;
    local_24 = param_2;
    iVar1 = FUN_0003a934(param_1,&local_30);
    if (iVar1 == 1) {
      iVar1 = FUN_00051cb0(&local_24,0);
      if (*(int *)(param_1 + 0x40) != 0) {
        FUN_00052350(param_1);
        uVar2 = FUN_00051c88();
        if (*(uint *)(param_1 + 0x40) <= uVar2) goto LAB_00051e2e;
      }
      if ((*(char **)(param_1 + 0x3c) != (char *)0x0) && (**(char **)(param_1 + 0x3c) != '\0')) {
        local_28 = 0;
        do {
          if (*(char *)(*(int *)(param_1 + 0x3c) + local_28) == '\0') goto LAB_00051e2e;
          iVar3 = FUN_00051cb0(*(int *)(param_1 + 0x3c),&local_28);
        } while (iVar3 != iVar1);
      }
      if ((int)((uint)*(byte *)(param_1 + 0x70) << 0x1d) < 0) {
        FUN_00059fec(param_1);
      }
      if ((*(int *)(param_1 + 0x30) != 0) &&
         (pcVar4 = (char *)FUN_000491e8(*(undefined4 *)(param_1 + 0x2c)), *pcVar4 == '\0')) {
        FUN_0004d3d8(param_1);
      }
      FUN_000491f4(*(undefined4 *)(param_1 + 0x2c),*(undefined4 *)(param_1 + 0x4c),&local_30);
      FUN_00051f94(param_1);
      if ((int)((uint)*(byte *)(param_1 + 0x70) << 0x1d) < 0) {
        iVar1 = FUN_00050a64(*(undefined4 *)(param_1 + 0x34));
        iVar3 = FUN_00050a64(&local_30);
        iVar1 = FUN_0004f588(*(undefined4 *)(param_1 + 0x34),iVar1 + iVar3 + 1);
        *(int *)(param_1 + 0x34) = iVar1;
        if (iVar1 == 0) {
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        FUN_00051a80(iVar1,*(undefined4 *)(param_1 + 0x4c),&local_30);
        FUN_00024664(param_1);
      }
      FUN_00052370(param_1,*(int *)(param_1 + 0x4c) + 1);
      FUN_0004e5a6(param_1,0x20,0);
    }
  }
LAB_00051e2e:
  return CONCAT44(iStack_2c,local_30);
}

