/* Address: 0004137c; name: FUN_0004137c; body bytes: 130 */

undefined1 *
FUN_0004137c(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            int param_5)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  
  puVar1 = (undefined1 *)FUN_0004a360(0x1c);
  if (puVar1 == (undefined1 *)0x0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (param_5 == 0) {
    param_5 = FUN_00041788(param_2,param_4);
  }
  uVar2 = FUN_00020316(param_2,param_3,param_4,param_5);
  if (((code *)*param_1 == (code *)0x0) || (iVar3 = (*(code *)*param_1)(uVar2,param_4), iVar3 == 0))
  {
    FUN_00046bec(puVar1);
    puVar1 = (undefined1 *)0x0;
  }
  else {
    *(short *)(puVar1 + 4) = (short)param_2;
    *(short *)(puVar1 + 6) = (short)param_3;
    puVar1[1] = (char)param_4;
    *(undefined2 *)(puVar1 + 2) = 0x30;
    *(short *)(puVar1 + 8) = (short)param_5;
    *puVar1 = 0x19;
    uVar4 = FUN_000411a4(iVar3,param_4);
    *(undefined4 *)(puVar1 + 0xc) = uVar2;
    *(undefined4 *)(puVar1 + 0x10) = uVar4;
    *(int *)(puVar1 + 0x14) = iVar3;
    *(undefined4 **)(puVar1 + 0x18) = param_1;
  }
  return puVar1;
}

