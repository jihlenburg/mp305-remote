/* Address: CODE:a16d; name: FUN_CODE_a16d; body bytes: 13 */

void FUN_CODE_a16d(undefined1 param_1)

{
  undefined1 uVar1;
  char *pcVar2;
  
  uVar1 = FUN_CODE_83d4();
  pcVar2 = (char *)(CONCAT11(param_1,uVar1) + 2);
  *pcVar2 = *pcVar2 + '\x01';
  return;
}

