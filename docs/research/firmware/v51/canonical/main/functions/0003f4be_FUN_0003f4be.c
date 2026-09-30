/* Address: 0003f4be; name: FUN_0003f4be; body bytes: 174 */

undefined8 FUN_0003f4be(int param_1,undefined4 param_2,uint param_3)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined2 local_24;
  undefined1 local_22;
  
  piVar1 = (int *)FUN_0004a200();
  if (piVar1 == (int *)0x0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  FUN_0004a57a(piVar1,0,0x14);
  iVar2 = FUN_0004a318(*(int *)(param_1 + 0x70) << 2);
  piVar1[1] = iVar2;
  if (iVar2 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if ((*(byte *)(param_1 + 0x74) & 7) == 3) {
    iVar2 = FUN_0004a318(*(int *)(param_1 + 0x70) << 2);
    *piVar1 = iVar2;
    if (iVar2 == 0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if (piVar1[1] == 0) {
      if (iVar2 != 0) {
        FUN_00046bec();
        *piVar1 = 0;
      }
      FUN_0004a2ac(param_1 + 0x2c,piVar1);
      FUN_00046bec(piVar1);
      piVar1 = (int *)0x0;
      goto LAB_0003f546;
    }
  }
  else {
    *piVar1 = 0;
  }
  local_24 = (undefined2)param_2;
  *(undefined2 *)(piVar1 + 2) = local_24;
  local_22 = (undefined1)((uint)param_2 >> 0x10);
  *(undefined1 *)((int)piVar1 + 10) = local_22;
  piVar1[3] = 0;
  uVar3 = piVar1[4];
  uVar4 = uVar3 & 0xfffffffa;
  piVar1[4] = uVar4;
  if ((int)(param_3 << 0x1d) < 0) {
    uVar4 = uVar4 | 8;
  }
  else {
    uVar4 = uVar3 & 0xfffffff2;
  }
  piVar1[4] = uVar4 & 0xffffffef | (param_3 & 1) << 4;
  puVar5 = (undefined4 *)piVar1[1];
  for (uVar3 = 0; uVar3 < *(uint *)(param_1 + 0x70); uVar3 = uVar3 + 1) {
    *puVar5 = 0x7fffffff;
    puVar5 = puVar5 + 1;
  }
LAB_0003f546:
  return CONCAT44(param_1,piVar1);
}

