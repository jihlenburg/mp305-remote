/* Address: 00048a8c; name: FUN_00048a8c; body bytes: 568 */

/* Recovered from stored Thumb pointer at 00048a88; callback identification is inferred until
   reviewed. */

void FUN_00048a8c(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined *puVar7;
  undefined4 uVar8;
  undefined4 extraout_r3;
  undefined4 unaff_r4;
  undefined4 unaff_r5;
  undefined4 unaff_r6;
  
  iVar1 = FUN_00046698();
  iVar2 = FUN_0003edc4();
  if (iVar2 == 0xffff) {
    return;
  }
  iVar2 = FUN_0003ed78(iVar1,iVar2);
  if (iVar2 == 0) {
    return;
  }
  iVar3 = thunk_FUN_00050a1a(iVar2,&DAT_00048c54);
  if (iVar3 == 0) {
    *(undefined1 *)(iVar1 + 0x4c) = 0;
    puVar7 = PTR_PTR_1ffe00d0;
LAB_00048b68:
    FUN_0003ee60(iVar1,puVar7);
    if ((*(byte *)(iVar1 + 0x4d) & 1) != 0) {
      FUN_0003ee46(iVar1,(&PTR_DAT_1ffe00f8)[*(byte *)(iVar1 + 0x4c)]);
      return;
    }
    iVar2 = FUN_0004a318(*(int *)(iVar1 + 0x38) << 1);
    FUN_0004a404(iVar2,(&PTR_DAT_1ffe00f8)[*(byte *)(iVar1 + 0x4c)],*(int *)(iVar1 + 0x38) << 1,
                 extraout_r3,unaff_r4,unaff_r5,unaff_r6);
    for (uVar6 = 0; uVar6 < *(uint *)(iVar1 + 0x38); uVar6 = uVar6 + 1) {
      *(ushort *)(iVar2 + uVar6 * 2) = *(ushort *)(iVar2 + uVar6 * 2) & 0xfbff;
    }
    FUN_0003ee46(iVar1,iVar2);
    FUN_00046bec(iVar2);
    return;
  }
  iVar3 = thunk_FUN_00050a1a(iVar2,&DAT_00048c5c);
  if (iVar3 == 0) {
    *(undefined1 *)(iVar1 + 0x4c) = 1;
    puVar7 = PTR_PTR_1ffe00d4;
    goto LAB_00048b68;
  }
  iVar3 = thunk_FUN_00050a1a(iVar2,&DAT_00048c60);
  if (iVar3 == 0) {
    *(undefined1 *)(iVar1 + 0x4c) = 2;
    puVar7 = PTR_PTR_1ffe00d8;
    goto LAB_00048b68;
  }
  iVar3 = thunk_FUN_00050a1a(iVar2,&DAT_00048c64);
  if ((iVar3 == 0) || (iVar3 = thunk_FUN_00050a1a(iVar2,&DAT_00048c68), iVar3 == 0)) {
    iVar2 = FUN_0004e5a6(iVar1,0x24,0);
    if (iVar2 != 1) {
      return;
    }
    iVar1 = *(int *)(iVar1 + 0x48);
    if (iVar1 == 0) {
      return;
    }
    uVar5 = 0x24;
  }
  else {
    iVar3 = thunk_FUN_00050a1a(iVar2,&DAT_00048c6c);
    if (iVar3 == 0) {
      iVar2 = FUN_0004e5a6(iVar1,0x23,0);
      if (iVar2 != 1) {
        return;
      }
      iVar1 = *(int *)(iVar1 + 0x48);
      if (iVar1 == 0) {
        return;
      }
    }
    else {
      if (*(int *)(iVar1 + 0x48) == 0) {
        return;
      }
      iVar3 = thunk_FUN_00050a1a(iVar2,"Enter");
      if ((iVar3 != 0) && (iVar3 = thunk_FUN_00050a1a(iVar2,&DAT_00048c78), iVar3 != 0)) {
        iVar3 = thunk_FUN_00050a1a(iVar2,&DAT_00048c7c);
        if (iVar3 == 0) {
          FUN_000520c6(*(undefined4 *)(iVar1 + 0x48));
          return;
        }
        iVar3 = thunk_FUN_00050a1a(iVar2,&DAT_00048c80);
        if (iVar3 == 0) {
          FUN_00052370(*(int *)(iVar1 + 0x48),*(int *)(*(int *)(iVar1 + 0x48) + 0x4c) + 1);
          return;
        }
        iVar3 = thunk_FUN_00050a1a(iVar2,&DAT_00048c84);
        if (iVar3 == 0) {
          FUN_00052128(*(undefined4 *)(iVar1 + 0x48));
          return;
        }
        iVar3 = thunk_FUN_00050a1a(iVar2,&DAT_00048c88);
        if (iVar3 != 0) {
          FUN_00051eb8(*(undefined4 *)(iVar1 + 0x48),iVar2);
          return;
        }
        iVar2 = FUN_0005230c(*(undefined4 *)(iVar1 + 0x48));
        pcVar4 = (char *)FUN_00052350(*(undefined4 *)(iVar1 + 0x48));
        if (*pcVar4 == '-') {
          FUN_00052370(*(undefined4 *)(iVar1 + 0x48),1);
          FUN_00052128(*(undefined4 *)(iVar1 + 0x48));
          uVar8 = 0x2b;
          uVar5 = *(undefined4 *)(iVar1 + 0x48);
        }
        else {
          if (*pcVar4 != '+') {
            FUN_00052370(*(undefined4 *)(iVar1 + 0x48),0);
            FUN_00051db8(*(undefined4 *)(iVar1 + 0x48),0x2d);
            uVar5 = *(undefined4 *)(iVar1 + 0x48);
            iVar2 = iVar2 + 1;
            goto LAB_00048c1a;
          }
          FUN_00052370(*(undefined4 *)(iVar1 + 0x48),1);
          FUN_00052128(*(undefined4 *)(iVar1 + 0x48));
          uVar8 = 0x2d;
          uVar5 = *(undefined4 *)(iVar1 + 0x48);
        }
        FUN_00051db8(uVar5,uVar8);
        uVar5 = *(undefined4 *)(iVar1 + 0x48);
LAB_00048c1a:
        FUN_00052370(uVar5,iVar2);
        return;
      }
      FUN_00051db8(*(undefined4 *)(iVar1 + 0x48),10);
      iVar2 = FUN_00052310(*(undefined4 *)(iVar1 + 0x48));
      if (iVar2 == 0) {
        return;
      }
      iVar1 = *(int *)(iVar1 + 0x48);
    }
    uVar5 = 0x23;
  }
  FUN_0004e5a6(iVar1,uVar5,0);
  return;
}

