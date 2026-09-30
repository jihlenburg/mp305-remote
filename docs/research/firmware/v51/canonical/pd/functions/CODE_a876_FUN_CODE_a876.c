/* Address: CODE:a876; name: FUN_CODE_a876; body bytes: 12 */

undefined1
FUN_CODE_a876(undefined1 *param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
             char param_5)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  
  puVar2 = (undefined1 *)CONCAT11(param_3,param_2);
  do {
    uVar1 = *puVar2;
    puVar2 = puVar2 + 1;
    *param_1 = uVar1;
    param_1 = param_1 + '\x01';
    param_5 = param_5 + -1;
  } while (param_5 != '\0');
  return param_4;
}

