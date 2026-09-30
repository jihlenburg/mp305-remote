/* Address: 00065c14; name: FUN_00065c14; body bytes: 64 */

void FUN_00065c14(void)

{
  int iVar1;
  int iVar2;
  
  if (DAT_1ffe0034 != 0) {
    DAT_1ffe001c = 1;
    return;
  }
  DAT_1ffe001c = 0;
  iVar1 = (0x1f - LZCOUNT(DAT_1ffe0010)) * 0x14;
  iVar2 = *(int *)(*(int *)(&DAT_1ffe0da0 + iVar1) + 4);
  *(int *)(&DAT_1ffe0da0 + iVar1) = iVar2;
  if (iVar2 == iVar1 + 0x1ffe0da4) {
    iVar2 = *(int *)(iVar2 + 4);
    *(int *)(&DAT_1ffe0da0 + iVar1) = iVar2;
  }
  DAT_1ffe0000 = *(undefined4 *)(iVar2 + 0xc);
  return;
}

