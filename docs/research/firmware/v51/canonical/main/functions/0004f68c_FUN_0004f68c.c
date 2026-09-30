/* Address: 0004f68c; name: FUN_0004f68c; body bytes: 186 */

void FUN_0004f68c(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined1 auStack_38 [16];
  int local_28;
  
  for (uVar5 = 0; uVar5 < *(uint *)(DAT_2003a430 + 0x25c); uVar5 = uVar5 + 1) {
    if (*(char *)(DAT_2003a430 + uVar5 + 0x23c) == '\0') {
      for (uVar4 = 0; uVar4 < *(uint *)(DAT_2003a430 + 0x25c); uVar4 = uVar4 + 1) {
        if ((*(char *)(DAT_2003a430 + uVar4 + 0x23c) == '\0') && (uVar5 != uVar4)) {
          local_28 = uVar4 * 0x10 + 0x3c;
          iVar6 = uVar5 * 0x10 + 0x3c;
          iVar1 = FUN_0003dc12(DAT_2003a430 + iVar6,local_28 + DAT_2003a430);
          if (iVar1 != 0) {
            FUN_0003dda2(auStack_38,DAT_2003a430 + iVar6,DAT_2003a430 + local_28);
            uVar2 = FUN_0003db14(auStack_38);
            iVar1 = FUN_0003db14(DAT_2003a430 + iVar6);
            iVar3 = FUN_0003db14(local_28 + DAT_2003a430);
            if (uVar2 < (uint)(iVar3 + iVar1)) {
              FUN_0003d9b6(DAT_2003a430 + iVar6,auStack_38);
              *(undefined1 *)(DAT_2003a430 + uVar4 + 0x23c) = 1;
            }
          }
        }
      }
    }
  }
  return;
}

