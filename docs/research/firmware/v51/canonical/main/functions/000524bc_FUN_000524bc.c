/* Address: 000524bc; name: FUN_000524bc; body bytes: 182 */

void FUN_000524bc(int param_1,int param_2,undefined4 param_3,int param_4)

{
  undefined4 uVar1;
  char *pcVar2;
  int iVar3;
  int local_18;
  
  if (param_2 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  local_18 = param_4;
  FUN_00051f94();
  if ((*(int *)(param_1 + 0x3c) == 0) && (*(int *)(param_1 + 0x40) == 0)) {
    FUN_00049974(*(undefined4 *)(param_1 + 0x2c),param_2);
    FUN_00052370(param_1,0x7fff);
  }
  else {
    FUN_00049974(*(undefined4 *)(param_1 + 0x2c),&DAT_00052574);
    FUN_00052370(param_1,0x7fff);
    if ((int)((uint)*(byte *)(param_1 + 0x70) << 0x1d) < 0) {
      **(undefined1 **)(param_1 + 0x34) = 0;
    }
    local_18 = 0;
    while (*(char *)(param_2 + local_18) != '\0') {
      FUN_00051cb0(param_2,&local_18);
      uVar1 = FUN_00051ba6();
      FUN_00051db8(param_1,uVar1);
    }
  }
  if ((*(int *)(param_1 + 0x30) != 0) &&
     (pcVar2 = (char *)FUN_000491e8(*(undefined4 *)(param_1 + 0x2c)), *pcVar2 == '\0')) {
    FUN_0004d3d8(param_1);
  }
  if ((int)((uint)*(byte *)(param_1 + 0x70) << 0x1d) < 0) {
    FUN_00046bec(*(undefined4 *)(param_1 + 0x34));
    iVar3 = FUN_00050a40(param_2);
    *(int *)(param_1 + 0x34) = iVar3;
    if (iVar3 == 0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    FUN_00059fec(param_1);
  }
  FUN_0004e5a6(param_1,0x20,0,local_18);
  return;
}

