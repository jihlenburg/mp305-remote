/* Address: 00023868; name: FUN_00023868; body bytes: 252 */

/* Recovered from stored Thumb pointer at 0003c978; callback identification is inferred until
   reviewed. */

void FUN_00023868(void)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  DAT_2003a4c5 = DAT_2003a4c5 == '\0';
LAB_0002394e:
  puVar4 = (undefined4 *)FUN_0004a118(&DAT_2003a4cc);
  do {
    if (puVar4 == (undefined4 *)0x0) {
      return;
    }
    iVar1 = FUN_000526fc(puVar4[0x14]);
    puVar4[0xd] = iVar1 + puVar4[0xd];
    uVar2 = FUN_00052708();
    puVar4[0x14] = uVar2;
    DAT_2003a4c4 = '\0';
    if ((*(byte *)(puVar4 + 0x15) & 3) >> 1 != (uint)DAT_2003a4c5) {
      uVar3 = *(byte *)(puVar4 + 0x15) & 0xfffffffd | (DAT_2003a4c5 & 1) << 1;
      *(char *)(puVar4 + 0x15) = (char)uVar3;
      if ((int)(uVar3 << 0x1d) < 0) {
LAB_000238fa:
        if (-1 < (int)puVar4[0xd]) {
          if ((int)puVar4[0xc] < (int)puVar4[0xd]) {
            puVar4[0xd] = puVar4[0xc];
          }
          iVar1 = (*(code *)puVar4[8])(puVar4);
          if (puVar4[10] == iVar1) {
LAB_00023932:
            if (DAT_2003a4c4 != '\0') goto LAB_0002394e;
          }
          else {
            puVar4[10] = iVar1;
            if ((code *)puVar4[1] != (code *)0x0) {
              (*(code *)puVar4[1])(*puVar4,iVar1);
            }
            if (DAT_2003a4c4 != '\0') goto LAB_0002394e;
            if ((code *)puVar4[2] != (code *)0x0) {
              (*(code *)puVar4[2])(puVar4,iVar1);
              goto LAB_00023932;
            }
          }
          if ((int)puVar4[0xd] < (int)puVar4[0xc]) goto LAB_0002395a;
          FUN_000237b0(puVar4);
        }
      }
      else if (-1 < (int)puVar4[0xd]) {
        if ((-1 < (int)(uVar3 << 0x1c)) && ((code *)puVar4[6] != (code *)0x0)) {
          iVar1 = (*(code *)puVar4[6])(puVar4);
          puVar4[9] = puVar4[9] + iVar1;
          puVar4[0xb] = iVar1 + puVar4[0xb];
        }
        FUN_0005b380(puVar4);
        if ((code *)puVar4[3] != (code *)0x0) {
          (*(code *)puVar4[3])(puVar4);
        }
        *(byte *)(puVar4 + 0x15) = *(byte *)(puVar4 + 0x15) | 4;
        FUN_0005b170(puVar4);
        goto LAB_000238fa;
      }
      if (DAT_2003a4c4 != '\0') goto LAB_0002394e;
    }
LAB_0002395a:
    puVar4 = (undefined4 *)FUN_0004a13c(&DAT_2003a4cc,puVar4);
  } while( true );
}

