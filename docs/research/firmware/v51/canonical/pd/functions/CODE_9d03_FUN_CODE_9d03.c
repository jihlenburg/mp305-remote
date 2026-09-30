/* Address: CODE:9d03; name: FUN_CODE_9d03; body bytes: 19 */

void FUN_CODE_9d03(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  
  uVar1 = BANK0_R1;
  uVar3 = FUN_CODE_34fc();
  uVar2 = BANK0_R1;
  BANK0_R1 = uVar1;
  FUN_CODE_a90e(uVar2,uVar3,1,0,8);
  return;
}

