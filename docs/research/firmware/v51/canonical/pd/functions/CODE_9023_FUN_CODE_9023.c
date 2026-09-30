/* Address: CODE:9023; name: FUN_CODE_9023; body bytes: 35 */

void FUN_CODE_9023(byte param_1)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  
  puVar2 = &DAT_CODE_b930;
  uVar1 = (&DAT_CODE_b930)[param_1];
  if (param_1 == 1) {
    FUN_CODE_83dc(0xb3,uVar1);
    *puVar2 = 1;
  }
  else {
    FUN_CODE_83dc(0xb3,uVar1);
    *puVar2 = 0;
  }
  FUN_CODE_83f1();
  FUN_CODE_a9ae(uVar1,1);
  return;
}

