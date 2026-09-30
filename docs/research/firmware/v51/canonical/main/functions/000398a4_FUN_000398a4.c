/* Address: 000398a4; name: FUN_000398a4; body bytes: 152 */

void FUN_000398a4(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar1 = FUN_0004cd84(DAT_2003a474,4);
  if (iVar1 == 0) {
    return;
  }
  iVar2 = FUN_0004bbe2(DAT_2003a474);
  iVar1 = 0;
  if (*(int *)(param_1 + 0x74) != 0) {
    iVar1 = FUN_0004bbe2();
  }
  if (iVar2 == iVar1) {
    if (iVar2 == 0) {
      if (*(int *)(param_1 + 0x74) == DAT_2003a474) goto LAB_00039902;
      FUN_0004e5a6(*(int *)(param_1 + 0x74),0x11,DAT_2003a470);
      iVar1 = FUN_0003a5c8(param_1);
      if (iVar1 != 0) {
        return;
      }
      goto LAB_000398ee;
    }
LAB_000398cc:
    FUN_00047208(DAT_2003a474);
  }
  else {
    if (iVar1 == 0) {
      iVar4 = *(int *)(param_1 + 0x74);
      if (iVar4 != 0) {
        uVar3 = 0x11;
        goto LAB_00039918;
      }
    }
    else {
      iVar4 = *(int *)(param_1 + 0x74);
      if (iVar4 != 0) {
        if (iVar1 == 0) {
          uVar3 = 0x11;
        }
        else {
          uVar3 = 0x12;
        }
LAB_00039918:
        FUN_0004e5a6(iVar4,uVar3,DAT_2003a470);
        iVar1 = FUN_0003a5c8(param_1);
        if (iVar1 != 0) {
          return;
        }
      }
    }
    if (iVar2 != 0) goto LAB_000398cc;
LAB_000398ee:
    FUN_0004e5a6(DAT_2003a474,0x10,DAT_2003a470);
  }
  iVar1 = FUN_0003a5c8(param_1);
  if (iVar1 != 0) {
    return;
  }
LAB_00039902:
  *(int *)(param_1 + 0x74) = DAT_2003a474;
  return;
}

