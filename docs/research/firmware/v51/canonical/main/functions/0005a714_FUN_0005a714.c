/* Address: 0005a714; name: FUN_0005a714; body bytes: 146 */

void FUN_0005a714(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (*(int *)(DAT_2003a430 + 0x25c) != 0) {
    iVar3 = *(int *)(DAT_2003a430 + 0x25c);
    do {
      iVar2 = iVar3 + -1;
      iVar4 = 0;
      if (iVar2 < 0) break;
      iVar1 = iVar3 + 0x23b;
      iVar3 = iVar2;
      iVar4 = iVar2;
    } while (*(char *)(DAT_2003a430 + iVar1) != '\0');
    FUN_00040acc(DAT_2003a430,0x38,0);
    *(uint *)(DAT_2003a430 + 0x38) = *(uint *)(DAT_2003a430 + 0x38) & 0xfffffffe;
    *(uint *)(DAT_2003a430 + 0x38) = *(uint *)(DAT_2003a430 + 0x38) & 0xfffffffd;
    *(uint *)(DAT_2003a430 + 0x38) = *(uint *)(DAT_2003a430 + 0x38) | 0x20000;
    for (iVar3 = 0; iVar3 < *(int *)(DAT_2003a430 + 0x25c); iVar3 = iVar3 + 1) {
      if (*(char *)(DAT_2003a430 + iVar3 + 0x23c) == '\0') {
        if (iVar3 == iVar4) {
          *(uint *)(DAT_2003a430 + 0x38) = *(uint *)(DAT_2003a430 + 0x38) | 1;
        }
        *(uint *)(DAT_2003a430 + 0x38) = *(uint *)(DAT_2003a430 + 0x38) & 0xfffffffd;
        FUN_0005a2a8(DAT_2003a430 + iVar3 * 0x10 + 0x3c);
      }
    }
    *(uint *)(DAT_2003a430 + 0x38) = *(uint *)(DAT_2003a430 + 0x38) & 0xfffdffff;
  }
  return;
}

