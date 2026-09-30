/* Address: 00052128; name: FUN_00052128; body bytes: 142 */

void FUN_00052128(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  char *pcVar3;
  undefined4 local_10;
  
  if (*(int *)(param_1 + 0x4c) != 0) {
    local_10 = 0x7f;
    iVar1 = FUN_0003a934(param_1,&local_10);
    if (iVar1 == 1) {
      uVar2 = FUN_000491e8(*(undefined4 *)(param_1 + 0x2c));
      FUN_000516ec(uVar2,*(int *)(param_1 + 0x4c) + -1,1);
      FUN_00049974(*(undefined4 *)(param_1 + 0x2c),uVar2);
      FUN_00051f94(param_1);
      if ((*(int *)(param_1 + 0x30) != 0) &&
         (pcVar3 = (char *)FUN_000491e8(*(undefined4 *)(param_1 + 0x2c)), *pcVar3 == '\0')) {
        FUN_0004d3d8(param_1);
      }
      if ((int)((uint)*(byte *)(param_1 + 0x70) << 0x1d) < 0) {
        FUN_000516ec(*(undefined4 *)(param_1 + 0x34),*(int *)(param_1 + 0x4c) + -1,1);
        iVar1 = FUN_00050a64(*(undefined4 *)(param_1 + 0x34));
        iVar1 = FUN_0004f588(*(undefined4 *)(param_1 + 0x34),iVar1 + 1);
        *(int *)(param_1 + 0x34) = iVar1;
        if (iVar1 == 0) {
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
      }
      FUN_00052370(param_1,*(int *)(param_1 + 0x4c) + -1);
      FUN_0004e5a6(param_1,0x20,0);
    }
  }
  return;
}

