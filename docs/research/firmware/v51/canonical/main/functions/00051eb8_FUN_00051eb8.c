/* Address: 00051eb8; name: FUN_00051eb8; body bytes: 206 */

void FUN_00051eb8(int param_1,int param_2,undefined4 param_3,int param_4)

{
  undefined4 uVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  int local_18;
  
  if (param_2 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  local_18 = param_4;
  if ((int)((uint)*(byte *)(param_1 + 0x70) << 0x1d) < 0) {
    FUN_00059fec(param_1);
  }
  if ((*(int *)(param_1 + 0x3c) == 0) && (*(int *)(param_1 + 0x40) == 0)) {
    iVar2 = FUN_0003a934(param_1,param_2);
    if (iVar2 == 1) {
      if ((*(int *)(param_1 + 0x30) != 0) &&
         (pcVar3 = (char *)FUN_000491e8(*(undefined4 *)(param_1 + 0x2c)), *pcVar3 == '\0')) {
        FUN_0004d3d8(param_1);
      }
      FUN_000491f4(*(undefined4 *)(param_1 + 0x2c),*(undefined4 *)(param_1 + 0x4c),param_2);
      FUN_00051f94(param_1);
      if ((int)((uint)*(byte *)(param_1 + 0x70) << 0x1d) < 0) {
        iVar2 = FUN_00050a64(*(undefined4 *)(param_1 + 0x34));
        iVar4 = FUN_00050a64(param_2);
        iVar2 = FUN_0004f588(*(undefined4 *)(param_1 + 0x34),iVar2 + iVar4 + 1);
        *(int *)(param_1 + 0x34) = iVar2;
        if (iVar2 == 0) {
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        FUN_00051a80(iVar2,*(undefined4 *)(param_1 + 0x4c),param_2);
        FUN_00024664(param_1);
      }
      iVar4 = *(int *)(param_1 + 0x4c);
      iVar2 = FUN_00051c88(param_2);
      FUN_00052370(param_1,iVar4 + iVar2);
      FUN_0004e5a6(param_1,0x20,0,local_18);
      return;
    }
  }
  else {
    local_18 = 0;
    while (*(char *)(param_2 + local_18) != '\0') {
      FUN_00051cb0(param_2,&local_18);
      uVar1 = FUN_00051ba6();
      FUN_00051db8(param_1,uVar1);
    }
  }
  return;
}

