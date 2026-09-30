/* Address: ram:00007ffa; name: FUN_ram_00007ffa; body bytes: 160 */

undefined4 * FUN_ram_00007ffa(undefined4 *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  
  gp = &DAT_ram_20002000;
  if (DAT_ram_20002ed0 == 0) {
    FUN_ram_00007f90(&DAT_ram_20002eb8);
  }
  piVar2 = &DAT_ram_20002f00;
  do {
    puVar1 = (undefined4 *)piVar2[2];
    iVar3 = piVar2[1];
    while (iVar3 = iVar3 + -1, -1 < iVar3) {
      if (*(short *)(puVar1 + 3) == 0) {
        puVar1[0x19] = 0;
        *puVar1 = 0;
        puVar1[1] = 0;
        puVar1[2] = 0;
        puVar1[3] = 0xffff0001;
        puVar1[4] = 0;
        puVar1[5] = 0;
        puVar1[6] = 0;
        FUN_ram_00001d1a(puVar1 + 0x17,0,8);
        puVar1[0xd] = 0;
        puVar1[0xe] = 0;
        puVar1[0x12] = 0;
        puVar1[0x13] = 0;
        gp = &DAT_ram_20002000;
        return puVar1;
      }
      puVar1 = puVar1 + 0x1a;
    }
    if (*piVar2 == 0) {
      iVar3 = FUN_ram_00007f4a(param_1,4);
      *piVar2 = iVar3;
      if (iVar3 == 0) {
        *param_1 = 0xc;
        return (undefined4 *)0x0;
      }
    }
    piVar2 = (int *)*piVar2;
  } while( true );
}

