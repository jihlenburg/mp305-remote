/* Address: 0003cb6c; name: FUN_0003cb6c; body bytes: 136 */

undefined4 * FUN_0003cb6c(int *param_1)

{
  byte *pbVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  
  puVar2 = (undefined4 *)FUN_0004a162(&DAT_2003a4cc);
  if (puVar2 != (undefined4 *)0x0) {
    FUN_0004a404(puVar2,param_1,0x58);
    if ((int *)*param_1 == param_1) {
      *puVar2 = puVar2;
    }
    pbVar1 = (byte *)(puVar2 + 0x15);
    *pbVar1 = *pbVar1 & 0xfd | (DAT_2003a4c5 & 1) << 1;
    uVar3 = FUN_00052708();
    puVar2[0x14] = uVar3;
    if ((int)((uint)*pbVar1 << 0x1c) < 0) {
      if ((code *)puVar2[6] != (code *)0x0) {
        iVar4 = (*(code *)puVar2[6])(puVar2);
        puVar2[9] = puVar2[9] + iVar4;
        puVar2[0xb] = iVar4 + puVar2[0xb];
      }
      FUN_0005b380(puVar2);
      if ((param_1[1] != 0) || (param_1[2] != 0)) {
        FUN_0005b170(puVar2);
      }
      if ((code *)puVar2[1] != (code *)0x0) {
        (*(code *)puVar2[1])(*puVar2,puVar2[9]);
      }
      if ((code *)puVar2[2] != (code *)0x0) {
        (*(code *)puVar2[2])(puVar2,puVar2[9]);
      }
    }
    FUN_0002382c();
    return puVar2;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

