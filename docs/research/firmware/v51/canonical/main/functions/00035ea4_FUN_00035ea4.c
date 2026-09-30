/* Address: 00035ea4; name: FUN_00035ea4; body bytes: 96 */

/* Recovered from stored Thumb pointer at 00044fc4; callback identification is inferred until
   reviewed. */

undefined4 FUN_00035ea4(undefined4 param_1,int param_2)

{
  bool bVar1;
  ushort uVar2;
  int iVar3;
  byte bVar4;
  
  if ((*(char *)(param_2 + 4) == '\x05') || (*(char *)(param_2 + 4) == '\x06')) {
    iVar3 = *(int *)(param_2 + 0x4c);
    if (*(int *)(iVar3 + 0x38) != 0) {
      return 0;
    }
    if (*(int *)(iVar3 + 0x3c) != 0) {
      return 0;
    }
    if (((*(int *)(iVar3 + 0x2c) == 0) && (*(int *)(iVar3 + 0x30) == 0x100)) &&
       (*(int *)(iVar3 + 0x34) == 0x100)) {
      bVar4 = 0;
    }
    else {
      bVar4 = 1;
    }
    bVar1 = *(int *)(iVar3 + 0x68) != 0;
    if ((bool)(bVar1 & bVar4)) {
      return 0;
    }
    uVar2 = *(ushort *)(iVar3 + 0x20) >> 8;
    if (bVar1) {
      if (uVar2 == 0xe) {
        return 0;
      }
      if (uVar2 == 0x14) {
        return 0;
      }
    }
  }
  if (99 < *(byte *)(param_2 + 0x51)) {
    *(undefined1 *)(param_2 + 0x51) = 100;
    *(undefined1 *)(param_2 + 0x50) = 1;
  }
  return 0;
}

