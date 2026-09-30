/* Address: 0001814c; name: FUN_0001814c; body bytes: 100 */

void FUN_0001814c(void)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  
  iVar1 = DAT_1ffe0144;
  DAT_1ffe0243 = 0;
  DAT_1fffaadf = 0;
  DAT_1fffaae6 = 0;
  DAT_1ffe02b0 = 0;
  if (DAT_1ffe0144 != 0) {
    if (*(int *)(DAT_1ffe0144 + 0xc) != 0) {
      uVar2 = FUN_00037430(DAT_1ffe0144);
      FUN_0004e5a6(**(undefined4 **)(iVar1 + 0xc),0x11,uVar2);
      FUN_0004d3d8(**(undefined4 **)(iVar1 + 0xc));
      *(undefined4 *)(iVar1 + 0xc) = 0;
    }
    piVar3 = (int *)FUN_0004a118(iVar1);
    while (piVar3 != (int *)0x0) {
      if (*(int *)(*piVar3 + 8) != 0) {
        *(undefined4 *)(*(int *)(*piVar3 + 8) + 4) = 0;
      }
      piVar3 = (int *)FUN_0004a13c(iVar1);
    }
    FUN_0004a0d8(iVar1);
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

