/* Address: 00039838; name: FUN_00039838; body bytes: 108 */

void FUN_00039838(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = *(int *)(param_1 + 0xac);
  if (iVar1 != 0) {
    iVar3 = *(int *)(iVar1 + *(int *)(param_2 + 0xc) * 8);
    iVar1 = *(int *)(iVar1 + *(int *)(param_2 + 0xc) * 8 + 4);
    if ((*(char *)(param_2 + 0x12) == '\x01') &&
       ((*(int *)(param_1 + 0x38) != iVar3 || (*(int *)(param_1 + 0x3c) != iVar1)))) {
      FUN_0003a318(param_1);
    }
    iVar2 = FUN_0003a5c8(param_1);
    if (iVar2 == 0) {
      *(int *)(param_1 + 0x30) = iVar3;
      *(int *)(param_1 + 0x34) = iVar1;
      if (*(char *)(param_2 + 0x12) == '\x01') {
        FUN_0003a0ac(param_1);
      }
      else {
        FUN_0003a318();
      }
      iVar1 = FUN_0003a5c8(param_1);
      if (iVar1 == 0) {
        *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x30);
        *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x34);
      }
    }
  }
  return;
}

