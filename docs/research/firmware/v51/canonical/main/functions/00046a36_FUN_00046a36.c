/* Address: 00046a36; name: FUN_00046a36; body bytes: 148 */

undefined4 FUN_00046a36(undefined4 *param_1,int *param_2,undefined4 param_3,undefined4 param_4)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  if (param_1 == (undefined4 *)0x0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (param_2 == (int *)0x0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  *param_2 = 0;
  puVar4 = param_1;
  puVar5 = (undefined4 *)0x0;
  do {
    uVar3 = param_4;
    if ((int)((uint)*(byte *)(puVar4 + 5) << 0x1d) < 0) {
      uVar3 = 0;
    }
    iVar2 = (*(code *)*puVar4)(puVar4,param_2,param_3,uVar3);
    puVar6 = puVar5;
    if (iVar2 != 0) {
      if ((*(byte *)((int)param_2 + 0xf) & 1) == 0) {
        *param_2 = (int)puVar4;
        goto LAB_00046a9c;
      }
      puVar6 = puVar4;
      if (puVar5 != (undefined4 *)0x0) {
        puVar6 = puVar5;
      }
    }
    puVar4 = (undefined4 *)puVar4[7];
    puVar5 = puVar6;
  } while (puVar4 != (undefined4 *)0x0);
  if (puVar6 == (undefined4 *)0x0) {
    sVar1 = (short)((uint)(param_1[3] - ((int)param_1[3] >> 0x1f)) >> 1);
    *(short *)((int)param_2 + 6) = sVar1;
    *(short *)(param_2 + 1) = sVar1 + 2;
    *param_2 = 0;
    *(undefined2 *)(param_2 + 2) = *(undefined2 *)(param_1 + 3);
    *(undefined2 *)((int)param_2 + 10) = 0;
    *(undefined2 *)(param_2 + 3) = 0;
    *(undefined1 *)((int)param_2 + 0xe) = 1;
    *(undefined1 *)((int)param_2 + 0xf) = 1;
    uVar3 = 0;
  }
  else {
    if ((int)((uint)*(byte *)(puVar6 + 5) << 0x1d) < 0) {
      param_4 = 0;
    }
    (*(code *)*puVar6)(puVar6,param_2,param_3,param_4);
    *param_2 = (int)puVar6;
LAB_00046a9c:
    uVar3 = 1;
  }
  return uVar3;
}

